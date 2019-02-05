#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char keyType;
typedef char infoType;
typedef struct {
	keyType key;        // Keyword field
	infoType otherinfo; // Other field
}elemType;
typedef struct {
	elemType *R;        // Storage space base address
	int length;         // Current length
}SSTable;


// Sequentially search the data elements whose key is equal to key in the sequential table ST.
// If found, the function value is the position of the element in the table, otherwise it is 0.
int search_seq(SSTable ST, keyType key) {
	ST.R[0].key = key;                            // sentinel
	int i;
	for (i = ST.length; ST.R[i].key != key; --i); // Looking forward from the back
	return i;
}

// Binaryly search the data elements whose key is equal to key in the sequential table ST.
// If found, the function value is the position of the element in the table, otherwise it is 0.
int search_bin(SSTable ST, keyType key) {
	int low = 1;            // Set the element to be checked
	int high = ST.length;   // Set the element to be checked
	while (low<=high) {
		int mid = (low + high) / 2;
		if (key == ST.R[mid].key)
			return mid;     // Find the element to be checked
		else if (key < ST.R[mid].key)
			high = mid - 1; // Continue to look in the previous subtable
		else
			low = mid + 1;  // Continue to look in the next child table
	}
	return 0;               // There is no element to be checked in the table
}