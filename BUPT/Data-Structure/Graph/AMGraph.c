#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency matrix graph storage representation
#define MaxInt 32767            // Representing the maximum value
#define MVNum 100               // Maximum vertex number
typedef char vertexType;        // Suppose the data type of the vertex is character type
typedef int arcType;            // Suppose the weight type of the arc is integer type
typedef struct AMGraph {
	vertexType vexs[MVNum];     // Vertex table
	arcType arcs[MVNum][MVNum]; // Adjacency matrix
	int vexnum, arcnum;         // The current number of vertices and arcs of the graph
}AMGraph;


// Create an undirected network G using adjacency matrix notation
bool createUDN(AMGraph *G) {
	scanf("%d%d", G->vexnum, G->arcnum);       // Enter the total number of vertices, the total number of arcs
	for (int i = 0; i < G->vexnum; ++i)
		for (int j = 0; j < G->vexnum; ++j)
			G->arcs[i][j] = MaxInt;            // Initialize the adjacency matrix, the weight of the arc is set to the maximum value MaxInt
	for (int i = 0; i < G->arcnum; ++i) {      // Construct adjacency matrix
		int v1, v2;
		arcType w;
		scanf("%d%d%d", &v1, &v2, &w);         // Enter a vertex and weight attached to the arc
		v1 = locateVex(G, v1);                 // Determine the position of j in G, that is, the subscript of the vertex array
		v2 = locateVex(G, v2);                 // Determine the position of k in G, that is, the subscript of the vertex array
		G->arcs[v1][v2] = G->arcs[v2][v1] = w; // The weight of the edge <j,k> and its symmetric arc <k,j> is set to w
	}
	return true;
}


bool visited[MVNum];                   // Access the array of flags with an initial value of "false"
// Graph G is the adjacency matrix type
// Depth-first search traversal graph G from the v-th vertex
void DFS_AM(AMGraph G, int v) {
	printf("%d ", v);
	visited[v] = true;                 // Access the v-th vertex, and set the corresponding component of the access flag array to true
	for (int i = 0; i < G.vexnum; ++i) // Check the row of the adjacency matrix v in turn
		if (G.arcs[v][i] && !visited[i])
			DFS_AM(G, i);              // w is the adjacency point of v. If w is not accessed, recursively call DFS_AM
}


// Auxiliary array definition for recording the smallest weight from vertex set U to V-U
struct {
	vertexType adjvex; // The vertex of the smallest edge in U
	arcType lowcost;   // Weight on the smallest edge
}closedge[MVNum];

// The undirected network G is stored in the form of an adjacency matrix
// Constructing the minimum spanning tree T of G from the vertex u
// Output: the edges of the T
void miniSpanTree_Prim(AMGraph G, vertexType u) {
	int min = locateVex(G, u);                          // k is the subscript of vertex u
	for (int i = 0; i < G.vexnum; ++i)                  // Initialize closedge[i] for each vertex vi of V-U
		if (i != min) {
			closedge[i].adjvex = u;
			closedge[i].lowcost = G.arcs[min][i];
		}
	closedge[min].lowcost = 0;                          // Initialization, U={u}
	for (int i = 1; i < G.vexnum; ++i) {
		// Select the remaining n-1 vertices to generate n-1 edges
		min = Min(closedge);
		// Find the next node of T: the k-th vertex, the current minimum edge in closedge[k]
		vertexType u0 = closedge[min].adjvex;           // u0 is a vertex of the smallest edge, u0 belongs to U
		vertexType v0 = G.vexs[min];                    // V0 is the other vertex of the smallest side, v0 belongs to V-U
		printf("%c %c\n", u0, v0);                      // Output the current minimum edge (u0, v0)
		closedge[min].lowcost = 0;                      // The k-th vertex is merged into the U setk
		for (int j = 0; j < G.vexnum; ++j)
			if (G.arcs[min][j] < closedge[j].lowcost) { // Re-select the smallest edge after the new vertex is merged into U
				closedge[j].adjvex = G.vexs[min];
				closedge[j].lowcost = G.arcs[min][j];
			}
	}
}


#define arcnum 100
// Auxiliary array edge definition
struct {
	vertexType head; // Starting point of the edge
	vertexType tail; // Ending point of the edge
	arcType lowcost; // Weight on the edge
}edge[arcnum];

// Auxiliary array vexset definition
int vexset[MVNum];

// The undirected network G is stored in the form of an adjacency matrix
// Construct the minimum spanning tree of G
// Output: the edges of the T
void miniSpanTree_Kruskal(AMGraph G) {
	Sort(edge);                                            // Sort the elements in the array edge from small to large
	for (int i = 0; i < G.vexnum; ++i)                     // Auxiliary array, indicating that each vertex is a connected component
		vexset[i] = i;
	for (int i = 0; i < G.arcnum; ++i) {
		int vs1 = vexset[locateVex(G, edge[i].head)];      // Get the connected component vs1 at the start of the edge edge[i]
		int vs2 = vexset[locateVex(G, edge[i].tail)];      // Get the connected component vs2 at the end of the edge edge[i]
		if (vs1 != vs2) {                                  // The two vertices of the edge belong to different connected components
			printf("%c %c\n", edge[i].head, edge[i].tail); // Output this edge
			for (int j = 0; j < G.vexnum; ++j)             // Combine the two components of vs1 and vs2, that is, the two sets are uniformly numbered
				if (vexset[j] == vs2)
					vexset[j] = vs1;
		}
	}
}


// Find the shortest path from the v0 vertex of the directed graph G to the remaining vertices using the Dijkstra algorithm
void shortestPath_Dijkstra(AMGraph G, int v0) {
	bool S[G.vexnum];
	arcType D[G.vexnum];
	int path[G.vexnum];
	for (int i = 0; i < G.vexnum; ++i) {    // n vertices are initialized in sequence
		S[i] = false;                       // S is initialized to an empty set
		D[i] = G.arcs[v0][i];               // Initialize the shortest path length from v0 to each end point to the weight on the arc
		path[i] = (D[i] < MaxInt) ? v0 : -1;
	}
	S[v0] = true;                           // Add v0 to S
	D[v0] = 0;                              // The distance from the source point to the source point is 0.
	//---Initialization ends, the main loop starts, each time the v0 to the shortest path of a vertex v is obtained, and v is added to the S set.
	for (int i = 1; i < G.vexnum; ++i) {    // Calculate the remaining n-1 vertices in turn
		int min = MaxInt;
		int v;
		for (int j = 0; j < G.vexnum; ++j)  // Select a current shortest path with an end point of v
			if (!S[j] && D[j] < min) {
				v = j;
				min = D[j];
			}
		S[v] = true;                        // Add v to S
		for (int j = 0; j < G.vexnum; ++j)  // Update the shortest path length from v0 to all vertices on the set V-S
			if (!S[j] && (D[v] + G.arcs[v][j] < D[j])) {
				D[j] = D[v] + G.arcs[v][j]; // Update D[j]
				path[j] = v;                // Change the predecessor of j to v
			}
	}
}


// Find the shortest path between each pair of vertices i and j in directed graph G by Floyd algorithm
void shortestPath_Floyd(AMGraph G) {
	arcType D[G.vexnum][G.vexnum];
	int path[G.vexnum];
	for (int i = 0; i < G.vexnum; ++i)           // Initialize known paths and distances between pairs of nodes
		for (int j = 0; j < G.vexnum; ++j) {
			D[i][j] = G.arcs[i][j];
			path[i] = (D[i][j] < MaxInt&&i != j) ? i : -1;
		}
	for (int i = 0; i < G.vexnum; ++i)
		for (int j = 0; j < G.vexnum; ++j)
			for (int k = 0; k < G.vexnum; ++k)   // The path from j through i to k is shorter
				if (D[j][i] + D[i][k] < D[j][k]) {
					D[j][k] = D[j][i] + D[i][k]; // Update D[j][k]
					path[j][k] = path[i][k];     // Change the precursor of k to i
				}
}