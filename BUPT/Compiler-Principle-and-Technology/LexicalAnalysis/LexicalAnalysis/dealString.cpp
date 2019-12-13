#include "data.h"
#include "tools.h"


static void stringError() {
	while (*curPt != '\n' && *curPt != '\0')
		movePt();
	fprintf(targetPointer, "<error, string>");
	fprintf(errorListPointer, "line%d not a string\n", lineCount);
	printf("line:%d not a string\n", lineCount);
}

extern int dealwithString() {
	int state = Q0;
	string s = "";
	char t;
	while (true) {
		char c = *curPt;
		switch (state) {
			case Q0:
				if (c == '"')
					state = Q1;
				else {
					stringError();
					return -1;
				}
				break;
			case Q1:
				switch (c) {
					case '\\':
						state = Q2;
						break;
					case '"':
						state = Q3;
						break;
					case '\n':
						stringError();
						return -1;
						break;
					default:
						s.append(1, c);
				}
				break;
			case Q2:
				if (c == '\n')
					lineCount++;
				else
					s.append(1, c);
				state = Q1;
				break;
			case Q3:
				stringCount++;
				fprintf(targetPointer, "<string, \"%s\">", s.c_str());
				return 0;
				break;
		}
		movePt();
	}
}
