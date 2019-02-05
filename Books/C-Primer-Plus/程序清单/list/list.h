//list.h -- Simple list type header file

#pragma once

#include <stdbool.h>

//Statement of a specific program

#define TSIZE 45 //Store the array size of the movie name

typedef struct film {
	char title[TSIZE];
	int rating;
}Item;

//General type definition

typedef struct node {
	Item item;
	struct node *next;
}Node;

typedef struct node * List;

//Function prototype

//Action:         Initialize a linked list
//Prerequisite:   plist points to a linked list
//Postcondition:  the linked list is initialized to empty
void InitializeList(List *plist);

//Action:         Determine if the linked list is empty,
//                plist points to an initialized linked list
//Postcondition:  This function returns true if the linked list is empty;
//                otherwise returns false
bool ListIsEmpty(const List *plist);

//Action:         Determine if the linked list is full,
//                plist points to an initialized linked list
//Postcondition:  This function returns true if the linked list is full;
//                otherwise returns false
bool ListIsFull(void);

//Action:         Determine the number of items in the linked list,
//                plist points to an initialized linked list
//Postcondition:  This function returns the number of items in the linked list
unsigned int ListItemCount(const List *plist);

//Action:         Add an item at the end of the linked list
//Prerequisite:   item makes an item to be added to the linked list,
//                plist points to an initialized linked list
//Postcondition:  If possible,
//                the function adds an item at the end of the linked list and returns true;
//                otherwise returns false
bool AddItem(Item item, List *plist);

//Action:         Apply the function to each item in the linked list,
//                plist points to an initialized linked list
//                pfun points to a function that takes an argument of type Item with no return value
//Postcondition:  The function pointed to by pfun acts on each item in the linked list
void Traverse(const List*plist, void(*pfun)(Item item));

//Action:         Freed allocated memory (if any),
//                plist points to an initialized linked list
//Postcondition:  release all memory allocated for the linked list,
//                the linked list is set to empty
void EmptyTheList(List *plist);
