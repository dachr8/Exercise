//�ӿ�ʼλ�ã�start���ҳ������ڣ�end����ͨ·������start��end��������·���ĳ��ȡ�
//������ͼ�Թ�
//���Խ��ڵ���б�ţ���1��ʼ��ţ���Ŵ�����ϵ��£������ң�����ÿ���ߣ����������ڵ�֮���Ƿ��бߣ��������Ƿ��ܹ���ͨ��
//���߱������ļ��У��������˵�����ʾһ���ߣ�
//ÿ���ڵ�ķ�֧����һ����Ҫ����ݷ�֧�����������ķ������������ú㶨�ı�����������
//��Ҫ�ύ��Ʊ����Դ���룬Ҫ��͡�ʵ��һ��һ��
//���䣺�ҵ���start��end��һ����̵�·�������Թ��ж������Ӧ������ҵ�����ĳ��ڣ�

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Graph adjacency table storage representation
#define MVNum 20                // Maximum vertex number

typedef struct ArcNode {
	//Side node
	int adjVex;                 // The position of the vertex pointed to by the side
	struct ArcNode *nextArc;    // Pointer to the next side
}ArcNode;

typedef struct {
	//Vertex information
	ArcNode *firstArc;          // Pointer to a side attached to the vertex
}VNode, AdjList[MVNum];         // AdjList indicates the adjacency table type

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;         // The current number of vertices and sides of the graph
}ALGraph;

// Create an undirected graph G using the adjacency table notation
bool createUDG(ALGraph *G);

// Find the path to the exit from the start position and output it from start to end; output the length of the path
bool printShortestPath(ALGraph G, int start, int *end, int endNum);