#include "data.h"
#include "tools.h"

extern void dealwithPreprocess() {
	char c = *curPt;
	while (c != '\n' && c != '\0') {
		fprintf(targetPointer, "%c", c);
		movePt();
		c = *curPt;
	}
	fprintf(targetPointer, "\n");
}
