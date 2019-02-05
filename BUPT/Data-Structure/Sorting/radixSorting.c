#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAXNUM_KEY 8          // The maximum number of keyword items
#define RADIX 10              // Keyword radix, which is the base of the decimal integer
#define MAX_SPACE 10000

typedef int keyType;
typedef char infoType;
typedef struct SLCell {
	keyType keys[MAXNUM_KEY]; // Keyword
	infoType otheritems;      // Other data items
	int next;
}SLCell;
typedef struct SLList {
	SLCell r[MAX_SPACE];      // The available space of the static linked list, r[0] is the head node
	int keynum;               // The number of current keywords recorded
	int recnum;               // Current length of the static linked list
} SLList;
typedef int arrType[RADIX];


// The records in the r domain of the static linked list L have been ordered by (keys[0],...,keys[i-1])
// Create RADIX sublists by the i-th keyword keys[i] so that the keys[i] recorded in the same subtable are the same.
// f[0..RADIX-1] and e[0..RADIX-1] point to the first and last records in each sublist respectively
void distribute(SLCell *r, int i, arrType f, arrType e) {
	for (int j = 0; j < RADIX; ++j)
		f[j] = 0;                   // Each sublist is initialized to an empty list
	for (int p = r[0].next; p; p = r[p].next) {
		int j = ord(r[p].keys[i]); // ord maps the i-th keyword in the record to [0..RADIX-1]
		(f[j] ? r[e[j]].next : f[j]) = p;
		e[j] = p;                  // Insert the node pointed by p into the j-th sublist
	}
}

// According to keys[i], the sublists pointed to by f[0..RADIX-1] are linked into a linked list in order from small to large.
// e[0..RADIX-1] is the tail pointer of each subtable
void collect(SLCell *r, int i, arrType f, arrType e) {
	int j;
	for (j = 0; !f[j]; j = succ(j));                            // Find the first non-empty subtable, succ is a successor function
	r[0].next = f[j];                                           // r[0].next points to the first node of the first non-empty word table
	int t = e[j];
	while (j < RADIX) {
		for (j = succ(j); j < RADIX - 1 && !f[j]; j - succ(j)); // Find the next non-empty sublist
		if (f[j]) {                                             // Link two non-empty sublists
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;                                              // t points to the last node of the last non-empty sublist
}

// L is a static linked list sequential list
// Do a radix sort for L, so that L becomes an ordered static linked list from small to large, L->r[0] is the head node
void radixSort(SLList *L) {
	for (int i = 0; i < L->recnum; ++i)
		L->r[i].next = i + 1;
	L->r[L->recnum].next = 0;             // Transform L into a static linked list
	for (int i = 0; i < L->keynum; ++i) { // distribute and collect keywords by minimum priority
		arrType f, e;
		distribute(L->r, i, f, e);        // The i-th distribution
		collect(L->r, i, f, e);           // The i-th collection
	}
}