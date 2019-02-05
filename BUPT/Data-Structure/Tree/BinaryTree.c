#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Linked list binary tree storage representation
typedef char elemType;
typedef struct BiTNode {
	elemType data;                   // Node data field
	struct BiTNode *lchild, *rchild; // Left and right child pointers
}BiTNode, *BiTree;


// Recursive algorithm for traversing binary tree T in order
void inorderTraverse(BiTree T) {
	while (T) {                     // If the binary tree is not empty
		printf("%c", T->data);      // Access root node
		inorderTraverse(T->lchild); // Traversing the left subtree in order
		T = T->rchild;              // Traversing the right subtree
	}
}


// Enter the value of the node in the binary tree in the order of precedence,
// and create a binary tree T identified by the binary list
void createBiTree(BiTree *T) {
	char ch;
	scanf("%c", ch);
	if (ch == '#')
		*T = NULL;                      // Recursive end, empty tree
	else {                              // Recursively creating a binary tree
		*T = malloc(sizeof(BiTNode);    // Generate root node
		if (!*T)
			exit(1);

		(*T)->data = ch;                // Root node data field is set to ch
		createBiTree(&(*T)->lchild);    // Recursively create a left subtree
		createBiTree(&(*T)->rchild);    // Recursively create a right subtree
	}
}


// Copy a binary tree identical to T
void copy(BiTree T, BiTree *newT) {
	if (T) {
		*newT = malloc(sizeof(BiTNode));
		if (!*newT)
			exit(1);

		(*newT)->data = T->data;           // Copy root node
		copy(T->lchild, &(*newT)->lchild); // Recursively copying left subtree
		copy(T->rchild, &(*newT)->rchild); // Recursively copying right subtree
	} else
		*newT = NULL;
}


// Calculate the depth of the binary tree T
int depth(BiTree T) {
	if (T) {
		int m = depth(T->lchild); // Recursively calculate the depth of the left subtree as m
		int n = depth(T->rchild); // Recursively calculate the depth of the right subtree as n
		return max(m, n) + 1;     // The depth of the binary tree is the larger of m and n plus 1
	} else
		return 0;
}


// Count the number of nodes in the binary tree T
int nodeCount(BiTree T) {
	if (T)
		return nodeCount(T->lchild) + nodeCount(T->rchild) + 1;
	else
		return 0;
}