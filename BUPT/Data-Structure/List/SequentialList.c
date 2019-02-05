#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Sequential list storage structure
#define MAXSIZE 100 // The maximum length that the sequential list can reach
typedef char elemType;
typedef struct sqList {
	elemType *elem; // Base address of storage space
	int length;     // Current length
}sqList;


// Construct an empty sequential list L
bool initList(sqList *L) {
	L->elem = malloc(MAXSIZE * sizeof(elemType));
	if (!L->elem)
		exit(1);

	L->length = 0;
	return true;
}


bool getElem(sqList L, int i, elemType *e) {
	if (i<1 || i>L.length)
		return false;  // Determine if the value of i is reasonable, if it is not reasonable, return false

	e = L.elem[i - 1]; // Elem[i-1] unit stores the i-th data element
	return true;
}


// Find the data element with the value e in the sequential list L, and return its serial number.
int locateElem(sqList L, elemType e) {
	for (int i = 0; i < L.length; ++i)
		if (L.elem[i] == e)
			return i + 1; // Find success, return serial number i+1

	return 0;             // Find failed, return 0
}


// Insert a new element at the i-th position in the sequential list L.
// The legal range of the i-value is 1<=i<= L->length+1
bool listInset(sqList *L, int i, elemType e) {
	if (i<1 || i>L->length || L->length == MAXSIZE)
		return false;                // i-value is illegal or current storage is full

	for (int j = L->length - 1; j >= i - 1; --j)
		L->elem[j + 1] = L->elem[j]; // Insert position and subsequent elements move backward
	L->elem[i - 1] = e;              // Put the new element e in the i-th position
	++L->length;                     // List length plus 1
	return true;
}


// Delete the i-th element in the sequential list L
// The legal range of the i-value is 1<=i<=L->length
bool listDelete(sqList *L, int i) {
	if (i<1 || i>L->length)
		return false;                // i-value is illegal

	for (int j = i; j < L->length; ++j)
		L->elem[j - 1] = L->elem[j]; // The element after the deleted element moves forward
	--L->length;                     // List length minus 1
	return true;
}