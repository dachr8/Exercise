//从开始位置（start）找出到出口（end）的通路，并从start到end输出；输出路径的长度。
//采用下图迷宫
//可以将节点进行编号，从1开始编号，编号次序从上到下，从左到右；保存每条边，根据两个节点之间是否有边，来决定是否能够走通；
//将边保存在文件中，用俩个端点来表示一条边；
//每个节点的分支数不一样，要求根据分支数决定遍历的方向数，不能用恒定的遍历方向数。
//需要提交设计报告和源代码，要求和《实验一》一样
//补充：找到从start到end的一条最短的路径；当迷宫有多个出口应该如何找到最近的出口；

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