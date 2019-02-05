#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Sequential stack storage structure
#define MAXSIZE 100  // Initial allocation of sequential stack storage space
typedef char elemType;
typedef struct sqStack {
	elemType *base;  // Stack base pointer
	elemType *top;   // Stack top pointer
	int stacksize;   // Maximum available capacity of the stack
}sqStack;


// Construct an empty stack S
bool initStack(sqStack *S) {
	S->base = malloc(MAXSIZE * sizeof(elemType)); // Dynamically allocate an array space with a maximum capacity of MAXSIZE for the sequence stack
	if (!S->base)
		exit(1);                                  // Storage allocation failed

	S->top = S->base;                             // Top initial is base, empty stack
	S->stacksize = MAXSIZE;                       // Set stacksize to the maximum capacity of the stack MAXSIZE
	return true;
}


// Insert element e as the new top element
bool push(sqStack *S, elemType e) {
	if (S->top == S->base + S->stacksize)
		return false; // Stack is full

	*S->top++ = e;    // Push the element e onto the top of the stack, and increment the stack top pointer by 1.
	return true;
}


// Delete the top element of S and return its value with e
bool pop(sqStack *S, elemType *e) {
	if (S->top == S->base)
		return false; // Stack is empty

	e = *--S->top;    // Decrement the stack top pointer by 1, and set the top element of the stack to the e
	return true;
}


// Return the top element of S, without modifying the top pointer
elemType getTop(sqStack S) {
	if (S.top != S.base)     // Stack is not empty
		return *(S.top - 1); // Return the value of the top element of the stack, the top pointer is unchanged
}