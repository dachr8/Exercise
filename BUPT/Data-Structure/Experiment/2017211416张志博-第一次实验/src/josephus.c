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


// N����Χ��һȦ���ӵ�S����ʼ������ÿ����M������ɱ�������ʣ��X���������˶�����ɱ����
// ����N=6��S=1��M=5����ɱ�����˵����Ϊ5��4��6��2��3�����ʣ��1�š�

// �Ӽ�����������N��N<50����N���˵ı�ţ����ͣ����������Ա�����䣬��������ͷ�ڵ��ѭ������
// ���ѭ�����������ֵ��
// ���뿪ʼ�������˵ı��S������ĸ���M��ʣ������X��
// ��ѭ�������в��ҵ����ΪS�Ľ�㣻
// ��1��ʼ�����������M���ˣ���㣩��ѭ��������ɾ������������˵ı�ţ�
// �Ӹղű�ɾ���˵���һ���˿�ʼ�ظ�����5��ֱ�����ֻʣ�� X ����Ϊֹ��
// ������ʣ����˵ı�š��������Ա�����䡣

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