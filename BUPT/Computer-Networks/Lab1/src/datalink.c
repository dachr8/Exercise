#include <stdio.h>
#include <stdbool.h>

#include "protocol.h"
#include "datalink.h"


static bool no_nak = true;                       // no nak has been sent yet
static unsigned char oldest_frame = MAX_SEQ + 1; // initial value is only for the simulator

static unsigned char ack_expected = 0;		     // lower edge of sender's window
static unsigned char next_frame_to_end = 0;      // upper edge of sender's window +1
static unsigned char frame_expected = 0;         // lower edge of receiver's window
static unsigned char too_far = NR_BUFS;          // upper edge of receiver's window +1

static unsigned char out_buf[NR_BUFS][PKT_LEN];  // buffers for the outbound stream

static bool phl_ready = false;


static bool between(unsigned char a, unsigned char b, unsigned char c) {
	return a <= b && b < c || c < a && a <= b || b < c && c < a;
}

static unsigned char inc(unsigned char a) {
	return (a + 1) % (MAX_SEQ + 1);
}

static void put_frame(unsigned char* frame, int len) {
	*(unsigned int*)(frame + len) = crc32(frame, len);
	send_frame(frame, len + 4);
	phl_ready = false;
}

// construct and send a data, ack, or nak frame
static void send_frame_k(unsigned char fk, unsigned char frame_nr) {
	FRAME s;                                         // scratch variable

	s.kind = fk;                                     // kind == data, ack, or nak
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);

	switch (fk) {
	case FRAME_DATA:
		for (int i = 0; i < PKT_LEN; i++)
			s.data[i] = out_buf[frame_nr % NR_BUFS][i];
		s.seq = frame_nr;                            // only meaningful for data frames
		dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short*)s.data);
		put_frame((unsigned char*)& s, 3 + PKT_LEN); // transmit the frame
		start_timer(frame_nr % NR_BUFS, DATA_TIMER);
		break;
	case FRAME_ACK:
		dbg_frame("Send ACK  %d\n", s.ack);
		put_frame((unsigned char*)& s, 2);           // transmit the frame
		break;
	case FRAME_NAK:
		no_nak = false;
		dbg_frame("Send NAK  %d\n", s.ack);
		put_frame((unsigned char*)& s, 2);           // transmit the frame
		break;
	}
	stop_ack_timer();                                // no need for separte ack frame
}


int main(int argc, char** argv) {
	FRAME f;                                                    // scratch variable
	unsigned char in_buf[NR_BUFS][PKT_LEN];                     // buffers for the inbound stream
	bool arrived[NR_BUFS] = { 0 };                              // inbound bit map
	unsigned char nbuffered = 0;                                // initially no packets are buffered
	int len;
	int arg;

	protocol_init(argc, argv);
	lprintf("Designed by Zhibo Zhang, build: " __DATE__"  "__TIME__"\n");
	disable_network_layer();

	while (true) {
		int event = wait_for_event(&arg);

		switch (event) {
		case NETWORK_LAYER_READY:                               // accept, save, and transmit a new frame
			++nbuffered;                                        // expand the window
			get_packet(out_buf[next_frame_to_end % NR_BUFS]);   // fetch new packet
			send_frame_k(FRAME_DATA, next_frame_to_end);        // transmit the frame
			next_frame_to_end = inc(next_frame_to_end);         // advance upper window edge
			break;

		case PHYSICAL_LAYER_READY:
			phl_ready = true;
			break;

		case FRAME_RECEIVED:                                    // a data or control fraem has arrived
			len = recv_frame((unsigned char*)& f, sizeof f);    // fetch incoming frame from physical layer
			if (len < 5 || crc32((unsigned char*)& f, len) != 0) {
				dbg_event("**** Receiver Error, Bad CRC Checksum\n");
				if (no_nak)
					send_frame_k(FRAME_NAK, 0);                 // damaged frame
				break;
			}
			switch (f.kind) {
			case FRAME_DATA:                                    // an undamaged frame has arrived
				dbg_frame("Recv DATA %d %d, ID %d\n", f.seq, f.ack, *(short*)f.data);
				if (f.seq != frame_expected && no_nak)
					send_frame_k(FRAME_NAK, 0);
				else
					start_ack_timer(ACK_TIMER);
				if (between(frame_expected, f.seq, too_far) && !arrived[f.seq % NR_BUFS]) {
					// frames may be accepted in any order
					arrived[f.seq % NR_BUFS] = true;            // mark buffer as full
					for (int i = 0; i < PKT_LEN; i++)
						in_buf[f.seq % NR_BUFS][i] = f.data[i]; // insert data into buffer
					while (arrived[frame_expected % NR_BUFS]) {
						// pass frames and advance window
						put_packet(in_buf[frame_expected % NR_BUFS], len - 7);
						no_nak = true;
						arrived[frame_expected % NR_BUFS] = false;
						frame_expected = inc(frame_expected);   // advance lower edge of receiver's window
						too_far = inc(too_far);                 // advance upper edge of receiver's window
						start_ack_timer(ACK_TIMER);             // to see if a separate ack is needed
					}
				}
				break;
			case FRAME_ACK:
				dbg_frame("Recv ACK  %d\n", f.ack);
				break;
			case FRAME_NAK:
				dbg_frame("Recv NAK  %d\n", f.ack);
				if (between(ack_expected, (f.ack + 1) % (MAX_SEQ + 1), next_frame_to_end))
					send_frame_k(FRAME_DATA, (f.ack + 1) % (MAX_SEQ + 1));
				break;
			}
			while (between(ack_expected, f.ack, next_frame_to_end)) {
				--nbuffered;                                    // handle piggybacked ack
				stop_timer(ack_expected % NR_BUFS);             // frame arrived intact
				ack_expected = inc(ack_expected);               // advance lower edge of sender's window
			}
			break;
		case DATA_TIMEOUT:
			dbg_event("---- DATA %d timeout\n", arg);
			send_frame_k(FRAME_DATA, oldest_frame);             // time out
			break;
		case ACK_TIMEOUT:
			dbg_event("---- ACK %d timeout\n", arg);
			send_frame_k(FRAME_ACK, 0);                         // ack timer expired, send ack
			break;
		}

		if (nbuffered < NR_BUFS && phl_ready)
			enable_network_layer();
		else
			disable_network_layer();
	}
}
