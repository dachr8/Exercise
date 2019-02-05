#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Fixed length sequential string storage structure
#define MAXLEN 255       // Maximum length of the string
typedef struct SString {
	char ch[MAXLEN + 1]; // One-dimensional array of storage string
	int length;          // Current length of the string
}SString;


// Return the position of the pattern string T after the pos character in the main string S
// If it does not exist, return 0.
// Where T is not empty, 1<=pos<=S.length
int index_BF(SString S, SString T, int pos) {
	int i = 1;                                   // Initialization
	while ((pos <= S.length) && (i <= T.length)) // Both strings are not compared to the end of the string
		if (S.ch[pos] == T.ch[i]) {              // Continue to compare subsequent characters
			++pos;
			++i;
		} else {                                 // Pointer back and start matching again
			pos = pos - i + 2;
			i = 1;
		}
	return (i > T.length) ? (pos - T.length) : 0;
}


// Using the next function of the pattern string T to find the position of the T after the pos character in the main string S
// Where T is not empty, 1<=pos<=S.length
int index_KMP(SString S, SString T, int pos) {

	// Find the next function value of the pattern string T and store it in the array next
	int nextval[T.length];
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i < T.length) {
		if (!i || T.ch[i] == T.ch[j]) {
			++i;
			++j;
			nextval[i] = (T.ch[i] != T.ch[j]) ? j : nextval[j];
		} else
			i = nextval[i];
	}

	i = 1; // Initialization
	while (pos <= S.length&&i <= T.length) { // Both strings are not compared to the end of the string
		if (!i || S.ch[pos] == T.ch[i]) {    // Continue to compare subsequent characters
			++pos;
			++i;
		} else
			i = nextval[i];
	}
	return (i > T.length) ? (pos - T.length) : 0;
}