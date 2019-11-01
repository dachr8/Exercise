#include "data.h"
#include "tools.h"

constexpr auto COMMENT = 10;


extern int dealwithLookAhead() {
	char c = *curPt;
	char next;
	forwardPt++;
	updateBuffer();
	next = *forwardPt;
	switch (c) {
		case '/':
			if (next == '/' || next == '*') {
				forwardPt = curPt;
				charCount += 2;
				return COMMENT;
			} else if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, DIV>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<ARI_OP, DIV>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '<':
			if (next == '<') {
				curPt = forwardPt;
				forwardPt++;
				updateBuffer();
				next = *forwardPt;
				if (next == '=') {
					fprintf(targetPointer, "<ASSIGN_OP, LEFT>");
					curPt = forwardPt;
					charCount += 3;
					return -1;
				} else {
					fprintf(targetPointer, "<BIT_OP, LEFT>");
					forwardPt = curPt;
					charCount += 2;
					return -1;
				}
			} else if (next == '=') {
				fprintf(targetPointer, "<REL_OP, LE>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<REL_OP, LT>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '>':
			if (next == '>') {
				curPt = forwardPt;
				forwardPt++;
				updateBuffer();
				next = *forwardPt;
				if (next == '=') {
					fprintf(targetPointer, "<ASSIGN_OP, RIGHT>");
					curPt = forwardPt;
					charCount += 3;
					return -1;
				} else {
					fprintf(targetPointer, "<BIT_OP, RIGHT>");
					forwardPt = curPt;
					charCount += 2;
					return -1;
				}
			} else if (next == '=') {
				fprintf(targetPointer, "<REL_OP, GE>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<REL_OP, GT>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '=':
			if (next == '=') {
				fprintf(targetPointer, "<REL_OP, EQ>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<ASSIGN_OP, EQ>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '+':
			if (next == '+') {
				fprintf(targetPointer, "<ARI_OP, SELF_ADD>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, ADD>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			}
			else {
				fprintf(targetPointer, "<ARI_OP, ADD>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '-':
			if (next == '-') {
				fprintf(targetPointer, "<ARI_OP, SELF_SUB>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else if (next == '>') {
				fprintf(targetPointer, "<MEM_OP, pointer>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, SUB>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<ARI_OP, SUB>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '^':
			if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, XOR>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<BIT_OP, XOR>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '|':
			if (next == '|') {
				fprintf(targetPointer, "<LOG_OP, OR>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else if (next == '=') {
				fprintf(targetPointer, "<ARI_OP, OR>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<BIT_OP, OR>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '&':
			if (next == '&') {
				fprintf(targetPointer, "<LOG_OP, AND>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else if (next == '=') {
				fprintf(targetPointer, "<ARI_OP, AND>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<&, ->");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '%':
			if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, MOD>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<ARI_OP, MOD>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '*':
			if (next == '=') {
				fprintf(targetPointer, "<ASSIGN_OP, MUL>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<*, ->");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
		case '!':
			if (next == '=') {
				fprintf(targetPointer, "<REL_OP, NEQ>");
				curPt = forwardPt;
				charCount += 2;
				return -1;
			} else {
				fprintf(targetPointer, "<LOG_OP, NOT>");
				forwardPt = curPt;
				charCount += 1;
				return -1;
			}
			break;
	}
}
