//�ӿ�ʼλ�ã�start���ҳ������ڣ�end����ͨ·������start��end��������·���ĳ��ȡ�
//������ͼ�Թ�
//���Խ��ڵ���б�ţ���1��ʼ��ţ���Ŵ�����ϵ��£������ң�����ÿ���ߣ����������ڵ�֮���Ƿ��бߣ��������Ƿ��ܹ���ͨ��
//���߱������ļ��У��������˵�����ʾһ���ߣ�
//ÿ���ڵ�ķ�֧����һ����Ҫ����ݷ�֧�����������ķ������������ú㶨�ı�����������
//��Ҫ�ύ��Ʊ����Դ���룬Ҫ��͡�ʵ��һ��һ��
//���䣺�ҵ���start��end��һ����̵�·�������Թ��ж������Ӧ������ҵ�����ĳ��ڣ�


#include "maze.h"

bool createUDG(ALGraph *G) {
	// Create an undirected graph G using the adjacency table notation
	scanf("%d%d", &G->vexnum, &G->arcnum);       // Enter the total number of vertices, the total number of sides

	for (int i = 0; i < G->vexnum; ++i)
		G->vertices[i].firstArc = NULL;        // Initialize the pointer field of the header node to NULL

	for (int i = 0, v1, v2; i < G->arcnum; ++i) {
		scanf("%d%d", &v1, &v2);               // Enter two vertices attached to one side


		ArcNode *p1 = malloc(sizeof(ArcNode)); // Generate a new side node *p1
		ArcNode *p2 = malloc(sizeof(ArcNode)); // Generate another new side node *p2
		if (!p1 || !p2)
			return false;

		p1->adjVex = v2 - 1;                       // Adjacent point number is v2
		p1->nextArc = G->vertices[v1 - 1].firstArc;
		G->vertices[v1 - 1].firstArc = p1;         // Insert the new node *p1 into the side table header of vertex v1

		p2->adjVex = v1 - 1;                       // Adjacent point number is v1
		p2->nextArc = G->vertices[v2 - 1].firstArc;
		G->vertices[v2 - 1].firstArc = p2;         // Insert the new node *p2 into the side table header of vertex v2
	}
	return true;
}

// Use the DFS algorithm to find the shortest relative distance between the destination point and the starting point, stored in the length array.
static void getPath_DFS(ALGraph G, int currentVex, int length[]) {
	ArcNode *curentAdj = G.vertices[currentVex].firstArc;
	while (curentAdj) {
		if (length[currentVex] + 1 < length[curentAdj->adjVex]) {
			length[curentAdj->adjVex] = length[currentVex] + 1;
			getPath_DFS(G, curentAdj->adjVex, length);
		}
		curentAdj = curentAdj->nextArc;
	}
}

bool printShortestPath(ALGraph G, int start, int *end, int endNum) {
	// Find the path to the exit from the start position and output it from start to end; output the length of the path
	for (int i = 0; i < endNum; ++i)
		if (end[i]<1 || end[i]>MVNum)
			return false;

	int length[MVNum];
	length[start - 1] = 0;

	for (int i = 0; i < G.vexnum; ++i)
		if (i == start - 1)
			length[i] = 0;
		else
			length[i] = MVNum;

	getPath_DFS(G, start - 1, length);

	int shortestLength = MVNum, nearestEnd;
	for (int i = 0; i < endNum; ++i)
		if (length[end[i] - 1] < shortestLength) {
			shortestLength = length[end[i] - 1];
			nearestEnd = end[i] - 1;
		}

	int path[MVNum];
	ArcNode *current = G.vertices[nearestEnd].firstArc;
	path[shortestLength - 1] = nearestEnd;
	for (int i = shortestLength - 1; i > 0; --i) {
		while (length[current->adjVex] != i)
			current = current->nextArc;
		path[i-1] = current->adjVex;
		current = G.vertices[current->adjVex].firstArc;
	}


	printf("\nPath: %d", start);
	for (int i = 0; i < shortestLength; ++i)
		printf(" -> %d", path[i] + 1);
	printf("\nLength: %d", shortestLength);

	return true;
}
