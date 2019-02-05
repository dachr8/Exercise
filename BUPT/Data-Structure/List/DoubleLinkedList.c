#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Double linked list storage structure
typedef int elemType;
typedef struct duLNode {
	elemType data;         // Node data field
	struct duLNode *prior; // Point to direct precursor
	struct duLNode *next;  // Point to direct successor
}duLNode, *duLinkList;


// Insert element e before the i-th position in the double linked list L with the head node
bool listInsert_duL(duLinkList *L, int i, elemType e) {
	duLinkList p = getElem_duL(*L, i);      // Determine the position pointer p of the i-th element in L
	if (!p)
		return false;                       // When p is NULL, the i-th element does not exist.

	duLinkList s = malloc(sizeof(duLNode)); // Generate new node *s
	if (!s)
		exit(1);

	s->data = e;                            // Set the node *s data field to e
	s->prior = p->prior;                    // Insert node *s into L
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return true;
}


// Delete the i-th element in the double linked list L with the head node
bool listDelete_duL(duLinkList *L, int i) {
	duLinkList p = getElem_duL(*L, i);       /// Determine the position pointer p of the i-th element in L
	if (!p)
		return false;                       // When p is NULL, the i-th element does not exist.

	p->prior->next = p->next;               // Modify the successor pointer of the predecessor node of the deleted node
	p->next->prior = p->prior;              // Modify the predecessor pointer of the successor node of the deleted node

	free(p);
	return true;                            // Release the space of the deleted node
}