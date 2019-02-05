#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Graph adjacency list storage representation
#define MVNum 100            // Maximum vertex number
typedef char infoType;
typedef char vertexType;

// arc node
typedef struct arcNode {
	int adjvex;              // The position of the vertex pointed to by the arc
	struct arcNode *nextarc; // Pointer to the next arc
	int weight;
	infoType info;           // Information related to the arc
}arcNode;

// Vertex information
typedef struct VNode {
	vertexType data;
	arcNode *firstarc;       // Pointer to a arc attached to the vertex
}VNode, adjList[MVNum];      // AdjList indicates the adjacency list type

// Adjacency list
typedef struct ALGraph {
	adjList vertices;
	int vexnum, arcnum;      // The current number of vertices and arcs of the graph
}ALGraph;


// Create an undirected graph G using the adjacency list notation
bool createUDG(ALGraph *G) {
	scanf("%d%d", G->vexnum, G->arcnum);       // Enter the total number of vertices, the total number of arcs
	for (int i = 0; i < G->vexnum; ++i) {
		scanf("%d", G->vertices[i].data);      // Enter vertex value
		G->vertices[i].firstarc = NULL;        // Initialize the pointer field of the header node to NULL
	}
	for (int i = 0; i < G->arcnum; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);               //Enter two vertices attached to one arc

		v1 = locateVex(G, v1);                  // Determine the position of v1 in G, that is, the sequence number of the vertex in G->vertices
		v2 = locateVex(G, v2);                  // Determine the position of v2 in G, that is, the sequence number of the vertex in G->vertices

		arcNode *p1 = malloc(sizeof(arcNode)); // Generate a new arc node *p1
		if (!*p1)
			exit(1);

		p1->adjvex = v2;                       // Adjacent point number is k
		p1->nextarc = G->vertices[v1].firstarc;
		G->vertices[v1].firstarc = p1;         // Insert the new node *p1 into the arc table header of the vertex vj

		arcNode *p2 = malloc(sizeof(arcNode)); // Generate another new arc node *p2
		if (!*p2)
			exit(1);

		p2->adjvex = v1;                       // Adjacent point number is j
		p2->nextarc = G->vertices[v2].firstarc;
		G->vertices[v2].firstarc = p2;         // Insert the new node *p2 into the arc table header of the vertex vk
	}
	return true;
}


bool visited[MVNum];                     // Access the array of flags with an initial value of "false"
// Graph G is the adjacency list type
// Depth-first search traversal graph G from the vth vertex
void DFS_AL(ALGraph G, int v) {
	printf("%d ", v);
	visited[v] = true;                   // Access the v-th vertex, and set the corresponding component of the access flag array to true
	arcNode *p = G.vertices[v].firstarc; // p points to the first arc of the arc list of v
	while (p) {                          // arc node is not empty
		int w = p->adjvex;               // Indicates that w is the adjacency point of v
		if (!visited[w])
			DFS_AL(G, w);                // Recursively call DFS_AL if w is not accessed
		p = p->nextarc;                  // p points to the next arc node
	}
}


// Directed graph G uses adjacency list storage structure
// If G has no loop, generate a topology sequence topo[] and return true, otherwise false
bool topologicalSort(ALGraph G, int *topo[]) {
	int indegree[G.vexnum];
	findIndegree(G, &indegree);              // Find the indegree of each vertex and store it in the array indegree
	linkStack S;
	initStack(&S);                           // Stack S is initialized to empty
	for (int i = 0; i < G.vexnum; ++i)
		if (!indegree[i])
			push(&S, i);                     // Push vertex with 0 indegree

	int m = 0;                               // Count the output vertex, initially 0
	while (!stackEmpty(S)) {                 // Stack is not empty
		pop(&S, &i);                         // Pop the stack top vertex vi
		*topo[m] = i;                        // Save vi in the topological sequence array topo
		++m;                                 // Count output vertices
		arcNode *p = G.vertices[i].firstarc; // p points to the first adjacent point of vi

		for (int k = p->adjvex; i < length; p = p->nextarc) {
			--indegree[k];                   // The indegree of each adjacent point of vi is reduced by 1
			if (!indegree[k])
				push(&S, k);                 // If the indegree is reduced to 0, push it onto the stack.
		}
	}
	return m >= G.vexnum;
}


// G is the directed network stored in the adjacency list
// Output each crtical activities of G
bool crticalPath(ALGraph G) {
	int topo[];
	if (!topologicalSort(G, &topo))
		return false;

	int ve[G.vexnum];
	int vl[G.vexnum];

	// Find the earliest occurrence time of each event in topological order
	for (int i = 0; i < G.vexnum; ++i)                                     // Give the earliest occurrence time of each event an initial value of 0
		ve[i] = 0;
	for (int i = 0; i < G.vexnum; ++i)
		for (arcNode *p = G.vertices[topo[i]].firstarc; p; p = p->nextarc) // Update the earliest occurrence time of all adjacent vertices of topo[i] in sequence
			ve[p->adjvex] = max(ve[p->adjvex], ve[topo[i]] + p->weight);

	// Find the latest occurrence time of each event in topological order

	for (int i = 0; i < G.vexnum; ++i)                                     // Give the latest occurrence time of each event an initial value of ve[n-1]
		vl[i] = ve[n - 1];
	for (int i = n - 1; i >= 0; --i)
		for (arcNode *p = G.vertices[topo[i]].firstarc; p; p = p->nextarc) // Update the latest occurrence time of topo[i] according to the neighboring point of topo[i]
			vl[topo[i]] = min(vl[topo[i]], vl[p->adjvex] - p->weight);

	// Determine if each activity is a key activity

	for (int i = 0; i < G.vexnum; ++i) {       // Every time loop through vi for all activities of the activity start point
		for (arcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
			int e = ve[i];                     // Calculate the earliest start time of <vi,vj>
			int l = vl[p->adjvex] - p->weight; // Calculate the latest start time of <vi,vj>
			if (e == l)                        // If it is a key activity, output <vi,vj>
				printf("%c %c\n", G.vertices[i].data, G.vertices[p->adjvex].data);
		}
	}
}