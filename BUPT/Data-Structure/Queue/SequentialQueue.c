#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Sequential queue storage structure
#define MAXQSIZE 100
typedef char elemType;
typedef struct  sqQueue {
	elemType *base; // Base address of storage space
	int front;      // Head pointer
	int rear;       // Tail pointer
}sqQueue;


// Construct an empty queue Q
bool initQueue(sqQueue *Q) {
	Q->base = malloc(sizeof(elemType)*MAXQSIZE); // Allocate an array space with a maximum capacity of MAXQSIZE to the queue
	if (!Q->base)
		exit(1);                                 // Storage allocation failed

	Q->front = Q->rear = NULL;                   // Set the head and tail pointers to null, and the queue is empty
	return true;
}


// Return the number of elements of Q, that is, the length of the queue
int queueLength(sqQueue Q) {
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


// Insert element e as the new tail element of Q
bool enQueue(sqQueue *Q, elemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) // The tail pointer is equal to the head pointer after adding 1 to the loop meaning, indicating that the queue is full.
		return false;

	Q->base[Q->rear] = e;                    // Insert new elements into the end of the queue
	Q->rear = (Q->rear + 1) % MAXQSIZE;      // Queue tail pointer plus 1
	return true;
}


// Delete the head element of the Q, and return its value with e
bool deQueue(sqQueue *Q, elemType *e) {
	if (Q->front == Q->rear)
		return false;                     // Queue is empty

	*e = Q->base[Q->front];                // Save queue head element
	Q->front = (Q->front + 1) % MAXQSIZE; // Queue head pointer plus 1
	return true;
}


// Return the head element of Q, do not modify the head pointer
elemType getHead(sqQueue Q) {
	if (Q.front != Q.rear)      // Queue is not empty
		return Q.base[Q.front]; // Return the value of the head element of the queue, the head of the queue is unchanged
}