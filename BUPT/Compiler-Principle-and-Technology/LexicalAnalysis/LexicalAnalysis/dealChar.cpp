#include "data.h"
#include "tools.h"


static void charError() {
	while (*curPt != '\n' && *curPt != '\0')
		movePt();
	fprintf(targetPointer, "<error, not a char>");
	fprintf(errorListPointer, "<line:%d not a char>\n", lineCount);
	printf("line:%d char error\n", lineCount);
}


extern int dealwithChar() {
	int state = Q0;

	while (true) {
		char c = *curPt;
		switch (state) {
			case Q0:
				if (c == '\'')
					state = Q1;
				else {
					charError();
					return -1;
				}
				break;
			case Q1:
				if (c == '\'') {
					charError();
					return -1;
				} else if (c == '\n') {
					lineCount++;
					charError();
					return -1;
				} else if (c == '\\')
					state = Q2;
				else
					state = Q4;
				break;
			case Q2:
				if (c == '\n')
					state = Q3;
				else
					state = Q4;
				break;
			case Q3:
				if (c == '\\')
					state = Q4;
				else if (c == '\'') {
					charError();
					return -1;
				} else if (c == '\n') {
					charError();
					lineCount++;
					return -1;
				} else
					state = Q4;
				break;
			case Q4:
				if (c == '\\')
					state = Q5;
				else if (c == '\n') {
					charError();
					lineCount++;
					return -1;
				} else if (c == '\'') {
					letterCount++;
					fprintf(targetPointer, "<letter, '%c'>", c);
					return 1;
				}
				break;
			case Q5:
				if (c == '\n') {
					lineCount++;
					state = Q4;
				} else
					state = Q4;
				break;
		}
		movePt();
	}
}
