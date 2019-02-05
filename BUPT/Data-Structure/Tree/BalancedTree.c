#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define M 3                // The order of the B-tree is temporarily set to 3.
typedef char keyType;
typedef char record;
typedef struct BTNode {
	int keynum;            // The number of keywords in the node, that is, the size of the node
	struct BTNode *parent; // Pointing to the parent node
	keyType K[M + 1];      // Keyword vector, unit 0 is unused
	struct BTNode *ptr[M + 1];
	record *recptr[M + 1]; // Record pointer vector, unit 0 is unused
}BTNode, *BTree;
typedef struct result {
	BTNode *pt;            // Point to the found node
	int i;                 // 1..m, the keyword number in the node
	bool tag;              // True: the search succeeds, false: the search fails
}result;


// Search the keyword key on the m-th order B-tree T, and return the result (pt, i, tag)
// If the search is successful, the feature value tag=1, and the i-th keyword in the node pointed by the pointer pt is equal to the key.
// Otherwise, the feature value tag=0, the keyword equal to the key should be inserted between the i-th and i+1-th keys in the node pointed by the pointer pt.
result searchBTree(BTree T, keyType key) {
	BTree p = T;                // Initialization, p points to the node to be checked
	BTree q = NULL;             // Initialization, q points to the parent of p
	bool found = false;
	while (p && !found) {
		int i = search(p, key); // Find i in p->K[1..keynum] so that: p->K[i] <= key < p->K[i+1]
		if (i > 0 && p->K[i] == key)
			found = true;       // Find the keyword to be checked
		else {
			q = p;
			p = p->ptr[i];
		}
	}
	if (found)
		return (p, i, 1);       // The search is successful
	else
		return (q, i, 0);       // The search is unsuccessful, and return the key insertion position information.
}


// Insert a keyword key between K[i] and K[i+1] of the node *q on the m-th order B-tree T
// If cause the node to be too large, then carry out the necessary node splitting adjustment along the parent chain so that T still makes the m-order B-tree
bool insertBTree(BTree *T, keyType key, BTree q, int i) {
	BTree ap = NULL;
	bool finished = false;
	while (q && !finished) {
		insert(q, i, key, ap);    // Insert key and ap into q->key[i+1] and q->ptr[i+1] respectively
		if (q->keynum < M)
			finished = true;      // Insert completed
		else {                    // Split node *q
			int s = (M + 1) / 2;
			split(q, s, ap);
			key = q->K[s];        // Move q->K[s+1..m], q->ptr[s..m] and q->recptr[s+1..m] into the new node *ap
			q = q->parent;
			if (q)
				i = search(q, x); // Find the insertion position of the key in the parent node *q
		}
	}
	if (!finished)                // T is an empty tree or the root node has been split into nodes *q and *ap
		newRoot(T, q, key, ap);   // Generate a new root node *T with information (T,key,ap), the original T and ap are subtree pointers
}