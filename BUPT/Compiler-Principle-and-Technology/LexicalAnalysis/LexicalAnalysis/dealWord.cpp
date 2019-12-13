#include "data.h"
#include "tools.h"


static void wordError() {
	fprintf(targetPointer, "<error, identifier>");
	fprintf(errorListPointer, "line%d not an identifier\n", lineCount);
}

extern int dealwithWord() {
	int state = Q0;
	string s = "";
	while (true) {
		char c = *curPt;
		switch (state) {
			case Q0:
				if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_') {
					s.append(1, c);
					state = Q1;
				} else {
					wordError();
					return -1;
				}
				break;
			case Q1:
				if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_' || (c <= '9' && c >= '0'))
					s.append(1, c);
				else {
					NODE* t = keylist.getKey(s.c_str());
					int pos;
					if (t != NULL) {
						keywordCount++;
						fprintf(targetPointer, "<KEY,%s>", s.c_str());
						return 1;
					} else if ((pos = signalTable.hasElement(s)) != -1) {
						identifierCount++;
						fprintf(targetPointer, "<id, %c_%d>", s[0], pos);
						return 1;
					} else {
						identifierCount++;
						pos = signalTable.addElement(s, UNKNOWN);
						fprintf(targetPointer, "<id, %c_%d>", s[0], pos);
						return 1;
					}
				}
				break;
		}
		movePt();
	}
}
