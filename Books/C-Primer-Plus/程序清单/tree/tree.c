//tree.c -- Tree support function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//Local data type
typedef struct pair {
	Trnode *parent, *child;
}Pair;

//Prototype of local function
static Trnode *MakeNode(const Item *pi);
static bool ToLeft(const Item *i1, const Item *i2);
static bool ToRight(const Item *i1, const Item *i2);
static void AddNode(Trnode *new_node, Trnode *root);
static void InOrder(const Trnode *root, void(*pfun)(Item item));
static Pair SeekItem(const Item *pi, const Tree *ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode *root);

//Function definition
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
	if (TreeIsFull(ptree)) {
		fprintf(stderr, "Tree is full\n");
		return false;
	}
	if (SeekItem(pi, ptree).child) {
		fprintf(stderr, "Attempted to add duplicate item\n");
		return false;
	}

	Trnode *new_node = MakeNode(pi); //Point to new node
	if (!new_node) {
		fprintf(stderr, "Couldn't create node\n");
		return false;
	}
	//Successfully created a new node
	ptree->size++;

	if (ptree->root)
		AddNode(new_node, ptree->root); //Add a new node to the tree
	else
		ptree->root = new_node;         //The new node is the root node of the tree

	return true;
}

bool InTree(const Item *pi, const Tree *ptree) {
	return SeekItem(pi, ptree).child ? true : false;
}

bool DeleteItem(const Item *pi, Tree *ptree) {
	Pair look = SeekItem(pi, ptree);

	if (!look.child)
		return false;

	if (!look.parent) //Delete root node entry
		DeleteNode(&ptree->root);
	else if (look.parent->left == look.child)
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);
	ptree->size--;

	return true;
}

void Traverse(const Tree * ptree, void(*pfun)(Item item)) {
	if (ptree)
		InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree) {
	if (ptree)
		DeleteAllNodes(ptree->root);
	InitializeTree(ptree);
}

//Local function
static void InOrder(const Trnode *root, void(*pfun)(Item item)) {
	if (root) {
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}


static void DeleteAllNodes(Trnode *root) {
	Trnode *pright;

	if (root) {
		pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}


static void AddNode(Trnode *new_node, Trnode *root) {
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
	else {
		fprintf(stderr, "Location error in AddNote()\n");
		exit(1);
	}
}

static bool ToLeft(const Item *i1, const Item *i2) {
	int comp1;

	if ((comp1 = strcmp(i1->petname, i2->petname)) < 0 || (!comp1&&strcmp(i1->petkind, i2->petkind) < 0))
		return true;
	else
		return false;
}

static bool ToRight(const Item *i1, const Item *i2) {
	int comp1;

	if ((comp1 = strcmp(i1->petname, i2->petname)) > 0 || (!comp1&&strcmp(i1->petkind, i2->petkind) > 0))
		return true;
	else
		return false;
}

static Trnode *MakeNode(const Item *pi) {
	Trnode *new_node = (Trnode*)malloc(sizeof(Trnode));

	if (new_node) {
		new_node->item = *pi;
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

	while (look.child && !seek) {
		if (ToLeft(pi, &(look.child->item))) {
			look.parent = look.child;
			look.child = look.child->left;
		} else if (ToRight(pi, &(look.child->item))) {
			look.parent = look.child;
			look.child = look.child->right;
		} else
			seek = true;
	}

	return look;
}

//ptr is the address of the parent node pointer member pointing to the target node
static void DeleteNode(Trnode **ptr) {
	Trnode *tmp;

	if (!(*ptr)->left) {
		tmp = *ptr;
		*ptr = (*ptr)->right;
		free(tmp);
	} else if (!(*ptr)->right) {
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	} else {
		for (tmp = (*ptr)->left; tmp->right; tmp = tmp->right);
		tmp->right = (*ptr)->right;
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	}
}
