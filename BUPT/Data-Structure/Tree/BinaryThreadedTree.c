#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Binary threaded tree storage representation
typedef char elemType;
typedef struct BiThrNode {
	elemType data;
	struct BiThrNode *lchild, *rchild; // Left and right child pointers
	bool LTag, RTag;                   // Left and right signs
}BiThrNode, *BiThrTree;


// Pre is a global variable, its right child pointer is null at initialization,
// which is convenient to start threads at the leftmost point of the tree.
BiThrTree pre = { 0,0,0,0,0 };
void inThreading(BiThrTree p) {
	if (p) {
		inThreading(p->lchild); // Recursive thread left subtree 

		if (p->lchild)
			p->LTag = 0;
		else {
			p->LTag = 1;     // Add left thread to p
			p->lchild = pre; // The left child pointer of p points to pre (predecessor)
		}

		if (pre->rchild)
			pre->RTag = 0;
		else {
			pre->RTag = 1;   // Add right thread to pre
			pre->rchild = p; // The right child pointer of pre points to pre (successor)
		}
		pre = p;             // Keep pre-pointing to p's predecessor

		inThreading(p->rchild); // Recursive thread right subtree
	}
}


// Traverse and thread the binary tree T in order,
// and the thrt points to the head node.
void inorderThreading(BiThrTree *thrt, BiThrTree T) {
	*thrt = malloc(sizeof(BiThrNode); // Head node
	if (!*thrt)
		exit(1);
	(*thrt)LTag = 0;                  // The head node has a left child. If the tree is not empty, the left child is the root of the tree.
	(*thrt)->RTag = 1;                // The right child pointer of the head node is the right thread
	(*thrt)->rchild = *thrt;          // The right pointer points to itself when initializing
	if (T) {
		(*thrt)->lchild = T;          // The left child of the head node points to the root
		pre = *thrt;                  // Pre initial value points to the head node
		inThreading(T);               // Performing a sequential threading of a binary tree rooted at T
		pre->rchild = *thrt;          // Pre is the rightmost node, and the right thread of pre points to the head node
		pre->RTag = 1;
		(*thrt)->rchild = pre;        // The right clue of the head node points to pre
	} else
		(*thrt)->lchild = *thrt;
}


// T points to the head node, and the left chain lchild of the head node points to the root node
// Non-recursive algorithm for traversing binary threaded tree T in order
// Direct output for each data element
void inorderTraverse_Thr(BiThrTree T) {
	for (BiThrTree p = T->lchild; p != T; p = p->rchild;) {
		while (!p->LTag)
			p = p->lchild;          // Down the left child
		printf("%c ", p->data);     // Access the node whose left subtree is empty
		while (p->RTag && (p->rchild != T)) {
			p = p->rchild;
			printf("%c ", p->data); // Accessing successor nodes along the right clue
		}
	}
}