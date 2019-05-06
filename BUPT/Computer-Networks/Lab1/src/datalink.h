#define DATA_TIMER  2000
#define ACK_TIMER  400

#define MAX_SEQ 15 // should be 2^n-1
#define NR_BUFS ((MAX_SEQ+1)/2)

/* FRAME kind */
#define FRAME_DATA 1
#define FRAME_ACK  2
#define FRAME_NAK  3

/*
	DATA Frame
	+=========+========+========+===============+========+
	| KIND(1) | SEQ(1) | ACK(1) | DATA(240~256) | CRC(4) |
	+=========+========+========+===============+========+

	ACK Frame
	+=========+========+========+
	| KIND(1) | ACK(1) | CRC(4) |
	+=========+========+========+

	NAK Frame
	+=========+========+========+
	| KIND(1) | ACK(1) | CRC(4) |
	+=========+========+========+
*/



typedef struct FRAME {
	unsigned char kind;
	unsigned char ack;
	unsigned char seq;
	unsigned char data[PKT_LEN];
	unsigned int  padding;
} FRAME;