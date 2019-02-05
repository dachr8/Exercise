#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// LInked queue storage structure
typedef char elemType;
typedef struct QNode {
	elemType data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct  linkQueue {
	QueuePtr front;      // Head pointer
	QueuePtr rear;       // Tail pointer
}linkQueue;


// Construct an empty queue Q
bool initQueue(linkQueue *Q) {
	Q->front = Q->rear = malloc(sizeof(elemType)*MAXQSIZE); // Generate a new node as the head node, the head and tail pointers point to this node
	if (!Q->rear)
		exit(1);

	Q->front = NULL;                                        // Set the head pointer to null
	return true;
}


// Insert element e as the new tail element of Q
bool enQueue(linkQueue *Q, elemType e) {
	QueuePtr p = malloc(sizeof(QNode)); // Allocate node space for enqueue elements, point with pointer p
	if (!p)
		exit(1);

	p->data = e;                        // Set the new node data field to e
	p->next = NULL;
	Q->rear->next = p;                  // Insert a new node into the tail of the queue
	Q->rear = p;                        // Modify the tail pointer
	return true;
}


// Delete the head element of the Q, and return its value with e
bool deQueue(linkQueue *Q, elemType *e) {
	if (Q->front == Q->rear)
		return false;            // Queue is empty

	QueuePtr p = Q->front->next; // p points to the head of the queue
	*e = p->data;                // e save the value of the queue head element
	Q->front->next = p->next;    // Modify the pointer field of the head node
	if (Q->rear == p)
		Q->rear = Q->front;      // The last element is deleted, the tail pointer points to the head node
	free(p);                     // Free up space for the original queue head element
	return true;
}


// Return the head element of Q, do not modify the head pointer
elemType getHead(linkQueue Q) {
	if (Q.front != Q.rear)    // Queue is not empty
		return Q.front->data; // Return the value of the head element of the queue, the head of the queue is unchanged
}