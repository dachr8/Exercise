#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "josephus.h"

bool initCircLinkList(CLinkList *L) {
	// Construct an empty circular linked list L
	*L = malloc(sizeof(CLNode)); // Generate a new node as the head node, with the head pointer L pointing to the head node
	if (!*L)
		return false;
	(*L)->next = *L;
	return true;
}


void createCircLinkList(CLinkList *L, int n) {
	// Enter the value of n elements in positive order to create a circular linked list L with a head node
	*L = malloc(sizeof(CLNode));
	scanf("%d%s%s%d", &(*L)->data.number, (*L)->data.name, (*L)->data.gender, &(*L)->data.age);
	(*L)->next = *L;                           // First create an empty linked list with a leading node
	CLinkList r = *L;                          // Tail pointer r points to the head node
	for (int i = 1; i < n; ++i) {
		CLinkList node = malloc(sizeof(CLNode));
		if (!node)
			exit(1);
		scanf("%d%s%s%d", &node->data.number, node->data.name, node->data.gender, &node->data.age);
		node->next = *L;
		r->next = node;
		r = node;
	}
}


bool getElem(CLinkList L, int i, elemType *e) {
	// The value of the element is obtained from the circular link list L with the head node according to the sequence number i, and the value of the i-th data element in the L is returned by e.
	if (i <= 0)
		return false;                   // i-value is illegal

	CLinkList p = L;
	for (int j = 1; j < i&&p->next != L; ++j)
		p = p->next;                    // p points to the next node
	if (!p)
		return false;                   // i-value is illegal

	*e = p->data;                       // Take the data field of the i-th node
	return true;
}


bool listDelete(CLinkList *L, int number) {
	// In the circular linked list L with the head node, delete the first element with the number
	CLinkList p = *L;
	while (p->next->data.number != number)
		p = p->next;

	CLinkList find = p->next;
	p->next = p->next->next; // Change the pointer field of the node that deletes the node
	if (find == *L)
		*L = p;
	free(find);        // Release the space to delete the node
	return true;
}


// N个人围成一圈，从第S个开始报数，每隔第M个将被杀掉，最后剩下X个，其余人都将被杀掉。
// 例如N=6，S=1，M=5，被杀掉的人的序号为5，4，6，2，3，最后剩下1号。

// 从键盘输入人数N（N<50）及N个人的编号（整型）、姓名、性别和年龄，正向建立带头节点的循环链表；
// 输出循环链表各结点的值；
// 输入开始报数的人的编号S、间隔的个数M和剩余人数X；
// 在循环链表中查找到编号为S的结点；
// 从1开始向后报数，将报M的人（结点）从循环链表中删除，并输出该人的编号；
// 从刚才被删除人的下一个人开始重复步骤5，直至最后只剩下 X 个人为止；
// 输出最后剩余的人的编号、姓名、性别和年龄。

bool josephus(CLinkList *L, int *n, int s, int m, int x) {
	if (!L || s > *n || m <= 0 || x >= *n)
		return false;

	CLinkList p = *L;
	for (int i = 1; i < s; ++i) // Find the node numbered S in the circular linked list
		p = p->next;
	p = *L;
	while (*n > x) {
		for (int i = 1; i < m; ++i)// Count back from 1 and delete the person (node) from M from the circular list and output the person's number;
			p = p->next;
		printf("\nKILLED:   Number: %d  Name: %s  Gender: %s  Age: %d\n", p->data.number, p->data.name, p->data.gender, p->data.age);
		CLinkList p_next = p->next;
		listDelete(L, p->data.number);
		p = p_next;
		--*n;
	}
	return true;
}