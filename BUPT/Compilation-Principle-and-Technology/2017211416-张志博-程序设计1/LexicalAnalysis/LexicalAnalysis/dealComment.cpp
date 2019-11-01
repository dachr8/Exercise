#include "data.h"
#include "tools.h"


extern int dealwithComment() {
	int state = Q0;
	while (true) {
		char c = *curPt;
		switch (state) {
			case Q0:
				if (c == '/')
					state = Q1;
				break;
			case Q1:
				if (c == '/')
					state = Q2;
				else
					state = Q3;
				break;
			case Q2:
				if (c == '\n') {
					lineCount++;
					movePt();
					return 0;
				}
				break;
			case Q3:
				if (c == '\n' || c == '\0')
					lineCount++;
				else if (c == '*')
					state = Q4;
				break;
			case Q4:
				if (c == '\n') {
					lineCount++;
					state = Q3;
				} else if (c == '/' || c == '\0') {
					movePt();
					return 0;
				} else state = Q3;
				break;
		}
		movePt();
	}
}
