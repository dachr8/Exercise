#include "data.h"
#include "tools.h"


extern int dealwithPunctuation() {
	delimiterCount++;
	fprintf(targetPointer, "<%c, ->", *curPt);
	movePt();
	return 1;
}
