#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Linked list binary sort tree storage representation
typedef int keyType;
typedef char infoType;
typedef struct elemType {
	keyType key;                     // Keyword item
	infoType otherinfo;              // Other data items
}elemType;
typedef struct BSTNode {
	elemType data;                   // Node data field
	struct BSTNode *lchild, *rchild; // Left and right child pointers
}BSTNode, *BSTree;


// Recursively search a data element whose key is equal to key in the binary sort tree pointed to by the root pointer T
// If the search is successful, return a pointer to the node of the data element, otherwise return a null pointer
BSTree searchBST(BSTree T, keyType key) {
	if (!T || key == T->data.key)
		return T;                       // End of search
	else if (key < T->data.key)
		return searchBST(T->lchild, T); // Continue searching in the left subtree
	else
		return searchBST(T->rchild, T); // Continue searching in the right subtree
}


// When there is no data element with the keyword equal to e.key in the binary sort tree T, insert the element
void insertBST(BSTree *T, elemType e) {
	if (!T) {                               // Found the insertion position and end the recursion
		*T = malloc(sizeof(BSTNode));       // Generate a new node
		if (!*T)
			exit(1);
		(*T)->data = e;                     // The data field of the new node is set to e
		(*T)->lchild = (*T)->rchild = NULL; // New node as leaf node
	} else if (e.key < (*T)->data.key)
		insertBST(&(*T)->lchild, e);        // Insert e into the left subtree
	else if (e.key > (*T)->data.key)
		insertBST(&(*T)->rchild, e);        // Insert e into the right subtree
}


#define ENDFLAG -1
// Read a node whose key is key in turn, and insert this node into the binary sort tree T.
void createBST(BSTree *T) {
	*T = NULL;                 // Initialize the binary sort tree T to an empty tree
	elemType e;
	scanf("%d", &e.key);
	while (e.key != ENDFLAG) { // ENDFLAG is a custom constant as an input end flag
		insertBST(T, e);       // Insert this node into the binary sort tree T
		scanf("%d", &e.key);
	}
}


// Delete the node whose key is equal to key from the binary sort tree T
bool deleteBST(BSTree *T, keyType key) {
	BSTree p = *T;   // Initialization
	BSTree f = NULL; // Initialization

	// The following while loop starts from the root to find the node with the keyword equal to the key *p

	bool flag = true;
	while (p&&flag)
		if (p->data.key == key) // Find the node *p with the keyword equal to the key, ending the loop
			flag = false;
		else {
			f = p;              // *f is the parent node of *p
			p = (p->data.key > key)£¿(p->lchild) :(p->rchild);
		}
	if (!p)
		return false;           // Return if the deleted node is not found

	// Consider the following three cases to realize the processing inside the subtree pointed to by p:
	// 1. *p's left and right subtrees are not empty
	// 2. *p's right subtree is empty
	// 3. *p's left subtree is empty

	BSTree q = p;
	if (p->lchild&&p->rchild) {                         // 1. The left and right subtrees of the deleted node *p are not empty.
		BSTree s;
		for (s = p->lchild; s->rchild; s = s->rchild)   // Continue to find its predecessor node in the left subtree of *p, the bottom right node
			q = s;
		p->data = s->data;                              // s points to the "predecessor" of the deleted node 
		((q == p) ? q->lchild : q->rchild) = s->lchild; // Reconnect the left/right subtree of *q
		free(s);
		return true;
	} else if (!p->rchild)                              // 2. The deleted node *p has no right subtree, just reconnect its left subtree
		p = p->lchild;
	else if (!p->lchild)                                // 3. The deleted node *p has no left subtree, just reconnect its right subtree
		p = p->rchild;

	// Attach the subtree pointed to by p to the position of its parent node *f

	if (f)
		((q == f->lchild) ? f->lchild : f->rchild) = p; // Attached to the left/right subtree location of *f
	else
		*T = p;                                         // The node being deleted is the root node  
	free(q);
	return true;
}