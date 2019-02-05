//tree.h -- Binary lookup number

#pragma once

#include <stdbool.h>

//Redefine Item according to specific situation
#define SLEN 20
typedef struct item {
	char petname[SLEN], petkind[SLEN];
}Item;

#define MAXITEMS 10

typedef struct trnode {
	Item item;
	struct trnode *left, *right; //Pointer to the left and right branches
}Trnode;

typedef struct tree {
	Trnode *root; //Pointer to the root node
	int size;     //Number of items in the tree
}Tree;

//Function prototype

//Action:         Initialize the tree to null
//Prerequisite:   ptree points to a tree
//Postcondition:  the tree is initialized to empty
void InitializeTree(Tree *ptree);

//Action:         Determine if the tree is empty
//Prerequisite:   ptree points to a tree
//Postcondition:  This function returns true if the tree is empty;
//                otherwise, it returns false
bool TreeIsEmpty(const Tree *ptree);

//Action:         Determine if the tree is full
//Prerequisite:   ptree points to a tree
//Postcondition:  This function returns true if the tree is full:
//                otherwise, it returns false
bool TreeIsFull(const Tree *ptree);

//Action:         Determine the number of items in the tree
//Prerequisite:   ptree points to a tree
//Postcondition:  Returns the number of items in the tree
int TreeItemCount(const Tree *ptree);

//Action:         Add an item to the tree
//Prerequisite:   pi is the address of the item to be added;
//                ptree points to an initialized tree
//Postcondition:  If you can add, the function will add an item to the tree and return true;
//                otherwise, return false
bool AddItem(const Item *pi, Tree *ptree);

//Action:         Find an item in the tree
//Prerequisite:   pi points to an item;
//                ptree points to an initialized tree
//Postcondition:  This function returns true if an item is looked up in the tree;
//                otherwise, it returns false
bool InTree(const Item *pi, const Tree *ptree);

//Action:         Delete an item in the tree
//Prerequisite:   pi is the address of the deleted item;
//                ptree points to an initialized tree
//Postcondition:  This function returns true if an item was successfully deleted from the tree;
//                otherwise, it returns false
bool DeleteItem(const Item *pi, Tree *ptree);

//Action:         Apply the function to each item in the tree
//Prerequisite:   ptree points to a tree;
//                pfun points to a function that accepts an Item type parameter with no return value
//Postcondition:  This function pointed to by pfun is executed once for each item in the tree
void Traverse(const Tree *ptree, void(*pfun)(Item item));

//Action:         Delete everything in the tree
//Prerequisite:   ptree points to an initialized tree
//Postcondition:  the tree is empty
void DeleteAll(Tree *ptree);
