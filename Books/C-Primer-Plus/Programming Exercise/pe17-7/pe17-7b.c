//pe17-7b.c -- copy of tree.c -- tree support functions

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pe17-7.h"

//local data type
typedef struct pair {
	Node *parent, *child;
} Pair;

//protototypes for local functions
static Node *MakeNode(const Item *pi);
static bool ToLeft(const Item *i1, const Item *i2);
static bool ToRight(const Item *i1, const Item *i2);
static void AddNode(Node *new_node, Node *root);
static void InOrder(const Node *root, void(*pfun)(Item item));
static Pair SeekItem(const Item *pi, const Tree *ptree);
static void DeleteNode(Node **ptr);
static void DeleteAllNodes(Node *ptr);

//function definitions
void InitializeTree(Tree *ptree) {
	ptree->root = ptree->size = NULL;
}

bool TreeIsEmpty(const Tree *ptree) {
	if (ptree->root)
		return false;
	else
		return true;
}

bool TreeIsFull(const Tree *ptree) {
	if (ptree->size == MAXITEMS)
		return true;
	else
		return false;
}

int TreeItemCount(const Tree *ptree) {
	return ptree->size;
}

bool AddItem(const Item *pi, Tree *ptree) {
	Pair seek;

	if (TreeIsFull(ptree)) {
		fprintf(stderr, "Tree is full\n");
		return false;
	}
	if ((seek = SeekItem(pi, ptree)).child) {
		seek.child->item.count++;
		return true;
	}

	Node *new = MakeNode(pi); //new points to new node
	if (!new) {
		fprintf(stderr, "Couldn't create node\n");
		return false;
	}
	//succeeded in creating a new node
	ptree->size++;

	if (ptree->root)
		AddNode(new, ptree->root); //add new node to tree
	else
		ptree->root = new;         //new node is tree root

	return true;
}

bool InTree(const Item *pi, const Tree *ptree) {
	return (SeekItem(pi, ptree).child) ? true : false;
}

const Item * WhereInTree(const Item *pi, const Tree *ptree) {
	Node *pn = SeekItem(pi, ptree).child;

	if (pn)
		return &(pn->item);
	else
		return NULL;
}

bool DeleteItem(const Item *pi, Tree *ptree) {
	Pair look = SeekItem(pi, ptree);

	if (!look.child)
		return false;
	if (look.child->item.count > 0)
		look.child->item.count--;
	else {
		if (!look.parent) //delete root item
			DeleteNode(&ptree->root);
		else if (look.parent->left == look.child)
			DeleteNode(&look.parent->left);
		else
			DeleteNode(&look.parent->right);
		ptree->size--;
	}

	return true;
}

void Traverse(const Tree *ptree, void(*pfun)(Item item)) {
	if (ptree)
		InOrder(ptree->root, pfun);
}

void DeleteAll(Tree *ptree) {
	if (ptree)
		DeleteAllNodes(ptree->root);
	ptree->root = ptree->size = NULL;
}

//local functions
static void InOrder(const Node *root, void(*pfun)(Item item)) {
	if (root) {
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}

static void DeleteAllNodes(Node *root) {
	if (root) {
		Node *pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}

static void AddNode(Node *new_node, Node *root) {
	if (ToLeft(&new_node->item, &root->item))
		if (root->left)
			AddNode(new_node, root->left);
		else
			root->left = new_node;
	else if (ToRight(&new_node->item, &root->item))
		if (root->right)
			AddNode(new_node, root->right);
		else
			root->right = new_node;
	else { //should be no duplicates
		fprintf(stderr, "location error in AddNode()\n");
		exit(1);
	}
}

static bool ToLeft(const Item *i1, const Item *i2) {
	if (strcmp(i1->wrd, i2->wrd) < 0)
		return true;
	else
		return false;
}

static bool ToRight(const Item *i1, const Item *i2) {
	if (strcmp(i1->wrd, i2->wrd) > 0)
		return true;
	else
		return false;
}

static Node *MakeNode(const Item *pi) {
	Node * new_node = (Node *)malloc(sizeof(Node));

	if (new_node) {
		new_node->item = *pi;
		new_node->item.count = 1;
		new_node->left = new_node->right = NULL;
	}

	return new_node;
}

static Pair SeekItem(const Item *pi, const Tree *ptree) {
	bool seek = false;
	Pair look;
	look.parent = NULL;
	look.child = ptree->root;

	if (!look.child)
		return look;
	while (!seek&&look.child)
		if (ToLeft(pi, &(look.child->item))) {
			look.parent = look.child;
			look.child = look.child->left;
		} else if (ToRight(pi, &(look.child->item))) {
			look.parent = look.child;
			look.child = look.child->right;
		} else           //must be same if not to left or right
			seek = true; //look.child is address of node with item

	return look;
}

static void DeleteNode(Node **ptr)
//ptr is address of parent member pointing to target node
{
	Node *tmp;

	if (!(*ptr)->left) {
		tmp = *ptr;
		*ptr = (*ptr)->right;
		free(tmp);
	} else if (!(*ptr)->right) {
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	} else { //deleted node has two children
			 //find where to reattach right subtree
		for (tmp = (*ptr)->left; tmp->right; tmp = tmp->right)
			continue;
		tmp->right = (*ptr)->right;
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	}
}
