// N����Χ��һȦ���ӵ�S����ʼ������ÿ����M������ɱ�������ʣ��X���������˶�����ɱ����
// ����N=6��S=1��M=5����ɱ�����˵����Ϊ5��4��6��2��3�����ʣ��1�š�

// �Ӽ�����������N��N<50����N���˵ı�ţ����ͣ����������Ա�����䣬��������ͷ�ڵ��ѭ������
// ���ѭ�����������ֵ��
// ���뿪ʼ�������˵ı��S������ĸ���M��ʣ������X��
// ��ѭ�������в��ҵ����ΪS�Ľ�㣻
// ��1��ʼ�����������M���ˣ���㣩��ѭ��������ɾ������������˵ı�ţ�
// �Ӹղű�ɾ���˵���һ���˿�ʼ�ظ�����5��ֱ�����ֻʣ�� X ����Ϊֹ��
// ������ʣ����˵ı�š��������Ա�����䡣


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