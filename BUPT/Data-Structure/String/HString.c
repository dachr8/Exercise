#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Heap sequential string storage structure
typedef struct HString {
	char *ch;   // If it is a non-empty string, the storage area is allocated according to the length of the string, otherwise ch is NULL.
	int length; // Current length of the string
}HString;