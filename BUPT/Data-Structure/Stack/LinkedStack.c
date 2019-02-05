#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Linked stack storage structure
typedef char elemType;
typedef struct stackNode {
	elemType data;
	struct stacknode *next;
}stackNode, *linkStack;


// Construct an empty stack S, the top pointer is blanked
bool initStack(linkStack *S) {
	*S = NULL;
	return true;
}


// Insert element e at the top of the stack
bool push(linkStack *S, elemType e) {
	linkStack p = malloc(sizeof(stackNode)); // Generate new nodes
	if (!p)
		exit(1);

	p->data = e;                             // Set the new node data field to e
	p->next = *S;                             // Insert a new node into the top of the stack
	*S = p;                                   // Modify the stack top pointer to p
	return true;
}


// Delete the top element of S and return its value with e
bool pop(linkStack *S, elemType *e) {
	if (!*S)
		return false; // Stack is empty

	e = (*S)->data;   // Set the top element of the stack to e
	linkStack p = *S; // Temporarily save the top element space with p for release
	*S = (*S)->next;  // Modify the top pointer
	free(p);          // Free up space on the original top element
	return true;
}


// Return the top element of S, without modifying the top pointer
elemType getTop(linkStack S) {
	if (!S)             // Stack is not empty
		return S->data; // Return the value of the top element of the stack, the top pointer is unchanged
}