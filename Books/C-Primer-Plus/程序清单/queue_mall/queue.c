//queue.c -- Queue type implementation

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Local function
static void CopyToNode(Item item, Node *pn);
static void CopyToItem(Node *pn, Item *pi);

void InitializeQueue(Queue *pq) {
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue *pq) {
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue *pq) {
	return pq->items == 0;
}

int QueueItemCount(const Queue *pq) {
	return pq->items;
}

bool EnQueue(Item item, Queue *pq) {
	if (QueueIsFull(pq))
		return false;

	Node *pnew = (Node*)malloc(sizeof(Node));
	if (!pnew) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;      //The item is at the head of the queue
	else
		pq->rear->next = pnew; //Link to the end of the queue
	pq->rear = pnew;           //Record the position of the end of the queue
	pq->items++;               //Number of queue items plus 1

	return true;
}

bool DeQueue(Item *pitem, Queue *pq) {
	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	Node *pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (!pq->items)
		pq->rear = NULL;

	return false;
}

void EmptyTheQueue(Queue *pq) {
	Item dummy;
	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
}

//Local function

static void CopyToNode(Item item, Node *pn) {
	pn->item = item;
}

static void CopyToItem(Node *pn, Item *pi) {
	*pi = pn->item;
}
