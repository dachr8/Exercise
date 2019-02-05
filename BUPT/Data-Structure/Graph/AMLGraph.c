#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Adjacency multilist list undirected graph storage representation
#define MAX_VERTEX_NUM 20
typedef char infoType;
typedef char vertexType;

typedef enum {
	unvisited, visited
}VisitIf;

typedef struct EBox {
	VisitIf mark;               // Access token
	int ivex, jvex;             // The position of the two vertices attached to the edge
	struct EBox *ilink, *jlink; // Point to the next edge attached to the two vertices
	infoType *info;             // The side information pointer
}EBox;

typedef struct vexBox {
	vertexType data;
	EBox *firstedge;            // Point to the first edge attached to the vertex
}vexBox;

typedef struct AMLGraph {
	vexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum;        // The current number of vertices and edges of the undirected graph
}AMLGraph;