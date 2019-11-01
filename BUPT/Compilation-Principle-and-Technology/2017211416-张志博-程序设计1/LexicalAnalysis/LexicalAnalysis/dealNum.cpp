#include "data.h"
#include "tools.h"


static void numberError() {
	while (*curPt != '\n' && *curPt != '\0')
		movePt();
	fprintf(targetPointer, "<error, not a number>");
	fprintf(errorListPointer, "line%d not a number\n", lineCount);
	printf("line:%d not a number\n", lineCount);
}

extern int dealwithNum() {
	int state = Q0;
	double ans = 0;
	double power = 0;
	double value = 1;
	int positive, powerPositive;
	if (*curPt == '+') {
		positive = 1;
		curPt++;
		forwardPt++;
	} else if (*curPt == '-') {
		positive = -1;
		curPt++;
		forwardPt++;
	} else
		positive = 1;

	while (true) {
		char c = *curPt;
		switch (state) {
			case Q0:
				switch (c) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						ans = ans * 10 + c - '0';
						break;
					case '.':
						state = Q1;
						break;
					case 'e':
						state = Q3;
						break;
					default:
						fprintf(targetPointer, "<num, %lf>", ans * positive);
						return 0;
						break;
				}
				break;
			case Q1:
				if (c < '0' || c>'9') {
					numberError();
					return -1;
				}
				value *= 0.1;
				ans += ((double)c - (double)'0') * value;
				state = Q2;
				break;
			case Q2:
				switch (c) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						value = value * 0.1;
						ans += value * ((double)c - (double)'0');
						break;
					case 'e':
						state = Q3;
						break;
					default:
						numberCount++;
						fprintf(targetPointer, "<num, %lf>", ans * positive);
						return 0;
						break;
				}
				break;
			case Q3:
				switch (c) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						powerPositive = 1;
						power = power * 10 + ((double)c - (double)'0') * powerPositive;
						state = Q4;
						break;
					case '+':
						powerPositive = 1;
						state = Q5;
						break;
					case '-':
						powerPositive = -1;
						state = Q5;
						break;
					default:
						numberError();
						return -1;
				}
				break;
			case Q4:
				if (c <= '9' && c >= '0')
					power = power * 10 + ((double)c - (double)'0') * powerPositive;
				else {
					ans = ans * pow(10, power);
					numberCount++;
					fprintf(targetPointer, "<num, %lf>", ans * positive);
					return 0;
				}
				break;
			case Q5:
				if (c <= '9' && c >= '0') {
					power = power * 10 + ((double)c - (double)'0') * powerPositive;
					state = Q4;
				} else {
					numberError();
					return -1;
				}
				break;
			case Q6:
				break;
		}
		movePt();
	}
}
