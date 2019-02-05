#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Linked string storage structure
#define CHUNKSIZE 80    // User-definable block size
typedef struct chunk {
	char ch[CHUNKSIZE];
	struct chunk *next;
}chunk;
typedef struct LString {
	chunk *head, *tail; // String head and tail pointer
	int length;         // Current length of the string
}LString;