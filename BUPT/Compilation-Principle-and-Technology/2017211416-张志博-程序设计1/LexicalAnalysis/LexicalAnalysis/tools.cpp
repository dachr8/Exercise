#include "data.h"
#include "tools.h"


extern void updateBuffer() {
	if (*forwardPt == 4) {
		forwardBuffer = !forwardBuffer;
		fread(buffer[forwardBuffer], 1, BUFFERLEN - 1, sourcePointer);
		forwardPt = buffer[forwardBuffer];
	}
}

extern void movePt() {
	forwardPt++;
	updateBuffer();
	curPt = forwardPt;
	charCount++;
}
