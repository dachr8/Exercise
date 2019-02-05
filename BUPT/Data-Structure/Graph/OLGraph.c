#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Orthogonal list directed graph storage representation
#define MAX_VERTEX_NUM 20
typedef char infoType;
typedef char vertexType;

typedef struct arcBox {
	int tailvex, headvex;          // The position of the tail and head vertices of the arc
	struct arcBox *hlink, *tlink;  // The chain domain of the arc with the same arc head and the same arc tail
	infoType *info;                // Pointer to the arc related information
}arcBox;

typedef struct vexNode {
	vertexType data;
	arcBox *firstin, *firstout;    // Point to the first in arc and out arc of the vertex
}vexNode;

typedef struct OLGraph {
	vexNode xlist[MAX_VERTEX_NUM]; // Head vector
	int vexnum, arcnum;            // The current number of vertices and arcs of the directed graph
}OLGraph;