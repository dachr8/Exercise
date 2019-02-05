#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Single linked list storage structure
typedef char elemType;
typedef struct LNode {
	elemType data;      // Node data field
	struct LNode *next; // Node pointer field
}LNode, *linkList;      // linkList is a pointer type to the structure LNode


// Construct an empty single linked list L
bool initList(linkList *L) {
	*L = malloc(sizeof(LNode)); // Generate a new node as the head node, with the head pointer L pointing to the head node
	if (!*L)
		exit(1);
	(*L)->next = NULL;          // The pointer field of the head node is blanked
	return true;
}


// The value of the element is obtained from the single linked list L with the head node according to the sequence number i,
// and the value of the i-th data element in the L is returned by e.
bool getElem(linkList L, int i, elemType *e) {
	if (i <= 0)
		return false;                // i-value is illegal

	linkList p = L->next;
	for (int j = 0; j < i && p; ++j) // The sequence field is scanned backwards until p is empty or p points to the i-th element
		p = p->next;                 // p points to the next node
	if (!p)
		return false;                // i-value is illegal

	*e = p->data;                    // Take the data field of the i-th node
	return true;
}


// Find the element with the value e in the single linked list L with the head node
linkList locateElem(linkList L, elemType e) {
	linkList p = L->next;       // Initialization, p points to the first node
	while (p && (p->data != e)) // The sequence field is scanned backwards until p is empty or the data field of the node pointed to by p is equal to e
		p = p->next;            // p points to the next node
	return p;                   // Find the node address p with a successful return value of e. The search fails p is NULL.
}


// Insert a new node with the value e at the i-th position in the single linked list L with the head node
bool listInsert(linkList *L, int i, elemType e) {
	if (i <= 0)
		return false;

	linkList p = *L;
	for (int j = 0; j < i - 1 && p; ++j)
		p = p->next;                    // Find the i-1-th node, p points to the node
	if (!p)
		return false;

	linkList s = malloc(sizeof(LNode)); // Generate new node *s
	if (!s)
		exit(1);
	s->data = e;                        // Set the data field of node *s to e
	s->next = p->next;                  // Point the pointer field of the node *s to the node ai
	p->next = s;                        // Point the pointer field of the node *p to the node *s
	return true;
}


// In the single linked list L with the head node, delete the i-th element
bool listDelete(linkList *L, int i) {
	if (i <= 0)
		return false;                   // Unreasonable deletion location

	linkList p = *L;
	for (int j = 0; j < i - 1 && p->next; ++j)
		p = p->next;                    // Find the i-1th node, p points to the node
	if (!p->next)
		return false;                   // Unreasonable deletion location

	linkList q = p->next;               // Temporarily save the address of the deleted node for release
	p->next = q->next;                  // Change the pointer field of the node that deletes the node
	free(q);                            // Release the space to delete the node
	return true;
}


// Enter the value of n elements in reverse order to create a single linked list L with the head node
void createList_H(linkList *L, int n) {
	*L = malloc(sizeof(LNode));
	if (!*L)
		exit(1);

	(*L)->next = NULL;                      // First create an empty linked list with the head node
	for (int i = 0; i < n; ++i) {
		linkList p = malloc(sizeof(LNode)); // Generate new node *p
		if (!p)
			exit(1);

		scanf("%c", p->data);               // The input element value is assigned to the data field of the new node *p
		p->next = (*L)->next;
		(*L)->next = p;                     // Insert the new node *p after the head node
	}
}


// Enter the value of n elements in positive order to create a single linked list L with the head node
void createList_R(linkList *L, int n) {
	*L = malloc(sizeof(LNode));
	if (!*L)
		exit(1);

	(*L)->next = NULL;                      // First create an empty linked list with the head node
	linkList r = *L;                        // Tail pointer r points to the head node
	for (int i = 0; i < n; ++i) {
		linkList p = malloc(sizeof(LNode)); // Generate new node *p
		if (!p)
			exit(1);

		scanf("%c", p->data);               // The input element value is assigned to the data field of the new node *p
		p->next = NULL;
		r->next = p;                        // Insert the new node *p after the tail node *r
		r = p;                              // r points to the new tail node *p
	}
}