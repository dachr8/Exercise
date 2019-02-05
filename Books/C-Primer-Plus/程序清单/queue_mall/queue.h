//qurue.h -- Queue interface

#pragma once

#include <stdbool.h>

#define MAXQUEUE 10

//Insert the definition of the Item type here, for example
typedef struct item {
	long arrive;     //When a customer joins the queue
	int processtime; //The time spent by the customer consultation
}Item;

typedef struct node {
	Item item;
	struct node *next;
}Node;

typedef struct queue {
	Node *front, *rear; //Pointer to the first and last items of the queue
	int items;          //Number of items in the queue
}Queue;

//Action:         Initialize the queue
//Prerequisite:   pq points to a queue
//Postcondition:  queue is initialized to empty
void InitializeQueue(Queue *pq);

//Action:         Check if the queue is full
//Prerequisite:   pq points to the queue that was previously initialized
//Postcondition:  Returns true if the queue is full, false otherwise
bool QueueIsFull(const Queue *pq);

//Action:         Check if the queue is empty
//Prerequisite:   pq points to the queue that was previously initialized
//Postcondition:  Returns true if the queue is empty, false otherwise
bool QueueIsEmpty(const Queue *pq);

//Action:         Determine the number of items in the queue
//Prerequisite:   pq points to the queue that was previously initialized
//Postcondition:  Returns the number of items in the queue
int QueueItemCount(const Queue *pq);

//Action:         Add an item at the end of the queue
//Prerequisite:   pq points to the queue that was previously initialized;
//                Item is the item to be added at the end of the queue
//Postcondition:  If the queue is not empty, the item will be added at the end of the queue, the function returns true;
//                otherwise, the queue does not change, the function returns false
bool EnQueue(Item item, Queue *pq);

//Action:         Remove an item from the beginning of the queue
//Prerequisite:   pq points to the queue that was previously initialized
//Postcondition:  If the queue is not empty, the item at the head of the queue will be copied to *pitem and deleted, and the function returns true;
//                if the operation makes the queue empty, the refill queue is empty;
//                if the queue is empty before the operation, the function returns false
bool DeQueue(Item *pitem, Queue *pq);

//Action:         Empty the queue
//Prerequisite:   pq points to the queue that was previously initialized
//Postcondition:  the queue is emptied
void EmptyTheQueue(Queue *pq);
