// N个人围成一圈，从第S个开始报数，每隔第M个将被杀掉，最后剩下X个，其余人都将被杀掉。
// 例如N=6，S=1，M=5，被杀掉的人的序号为5，4，6，2，3，最后剩下1号。

// 从键盘输入人数N（N<50）及N个人的编号（整型）、姓名、性别和年龄，正向建立带头节点的循环链表；
// 输出循环链表各结点的值；
// 输入开始报数的人的编号S、间隔的个数M和剩余人数X；
// 在循环链表中查找到编号为S的结点；
// 从1开始向后报数，将报M的人（结点）从循环链表中删除，并输出该人的编号；
// 从刚才被删除人的下一个人开始重复步骤5，直至最后只剩下 X 个人为止；
// 输出最后剩余的人的编号、姓名、性别和年龄。


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "josephus.h"



int main(void) {
	CLinkList list = NULL;
	int n;                         // Number of people
	int s, m, x;                   // The number S of the person who started the report, the number of intervals M, and the number of remaining people X;

	puts("Please input the number N(N < 50)");
	scanf("%d", &n);               // Read the number N(N < 50)
	
	if (!initCircLinkList(&list))  //assert(initCircLinkList(&list));
		return -1;
	printf("\n\nPlease input the number, name, gender, and age of the N person\n");
	createCircLinkList(&list, n);  // Read the number(integer), name, gender, and age of the N person from the keyboard, and establish a circular linked list with the head nodes

	for (int i = 1; i <= n; ++i) { // Output the value of each node of the circular linked list
		elemType e;
		if (getElem(list, i, &e))
			printf("\nNumber: %d  Name: %s  Gender: %s  Age: %d\n", e.number, e.name, e.gender, e.age);
	}

	printf("\n\nPlease input the number S of the person who started the report, the number of intervals M, and the number of remaining people X\n");
	scanf("%d%d%d", &s, &m, &x);   // Read the number S of the person who started the report, the number of intervals M, and the number of remaining people X;


	// Find the node numbered S in the circular linked list
	// Count back from 1 and delete the person (node) from M from the circular list and output the person's number
	// Repeat the steps from the next person who was just deleted, until only X people remain in the end
	josephus(&list, &n, s, m, x);


	printf("\n\nRemaining people:\n");
	for (int i = 1; i <= n; ++i) { // Output the number, name, gender, and age of the last remaining person
		elemType e;
		if (getElem(list, i, &e)) {
			printf("\nNumber: %d  Name: %s  Gender: %s  Age: %d\n", e.number, e.name, e.gender, e.age);
			listDelete(&list, list->data.number);
		}

	}

	system("pause");
	return 0;
}