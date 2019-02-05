// N����Χ��һȦ���ӵ�S����ʼ������ÿ����M������ɱ�������ʣ��X���������˶�����ɱ����
// ����N=6��S=1��M=5����ɱ�����˵����Ϊ5��4��6��2��3�����ʣ��1�š�

// �Ӽ�����������N��N<50����N���˵ı�ţ����ͣ����������Ա�����䣬��������ͷ�ڵ��ѭ������
// ���ѭ�����������ֵ��
// ���뿪ʼ�������˵ı��S������ĸ���M��ʣ������X��
// ��ѭ�������в��ҵ����ΪS�Ľ�㣻
// ��1��ʼ�����������M���ˣ���㣩��ѭ��������ɾ������������˵ı�ţ�
// �Ӹղű�ɾ���˵���һ���˿�ʼ�ظ�����5��ֱ�����ֻʣ�� X ����Ϊֹ��
// ������ʣ����˵ı�š��������Ա�����䡣


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