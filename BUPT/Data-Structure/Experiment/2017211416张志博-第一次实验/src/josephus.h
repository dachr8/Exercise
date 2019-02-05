// N个人围成一圈，从第S个开始报数，每隔第M个将被杀掉，最后剩下X个，其余人都将被杀掉。
// 例如N=6，S=1，M=5，被杀掉的人的序号为5，4，6，2，3，最后剩下1号。

// 从键盘输入人数N（N<50）及N个人的编号（整型）、姓名、性别和年龄，正向建立带头节点的循环链表；
// 输出循环链表各结点的值；
// 输入开始报数的人的编号S、间隔的个数M和剩余人数X；
// 在循环链表中查找到编号为S的结点；
// 从1开始向后报数，将报M的人（结点）从循环链表中删除，并输出该人的编号；
// 从刚才被删除人的下一个人开始重复步骤5，直至最后只剩下 X 个人为止；
// 输出最后剩余的人的编号、姓名、性别和年龄。


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Circular linked list storage structure
typedef struct INFO {
	int number;
	char name[20];
	char gender[10];
	int age;
}info;

typedef info elemType;
typedef struct CLNode {
	elemType data;       // Node data field
	struct CLNode *next; // Node pointer field
}CLNode, *CLinkList;     // Circular Linked List is a pointer type to the structure CLNode


// Construct an empty circular linked list L
bool initCircLinkList(CLinkList *L);

// Enter the value of n elements in positive order to create a circular linked list L with a head node
void createCircLinkList(CLinkList *L, int n);

// The value of the element is obtained from the circular link list L with the head node according to the sequence number i, and the value of the i-th data element in the L is returned by e.
bool getElem(CLinkList L, int i, elemType *e);

// In the circular linked list L with the head node, delete the first element with the number
bool listDelete(CLinkList *L, int number);

// Find the node numbered S in the circular linked list
// Count back from 1 and delete the person (node) from M from the circular list and output the person's number
// Repeat the steps from the next person who was just deleted, until only X people remain in the end
bool josephus(CLinkList *L, int *n, int s, int m, int x);