//list.c -- Functions that support linked list operations
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//Local function prototype
static void CopyToNode(Item item, Node *pnode);

//Interface function
//Set the linked list to empty
void InitializeList(List *plist) {
	*plist = NULL;
}

//Return true if the list is empty
bool ListIsEmpty(const List *plist) {
	if (*plist)
		return false;
	else
		return true;
}

//Return true if the list is full
bool ListIsFull(void) {
	List pt = (List)malloc(sizeof(Node));
	bool full;

	if (pt)
		full = false;
	else
		full = true;
	free(pt);

	return full;
}

//Return the number of nodes
unsigned int ListItemCount(const List *plist) {
	unsigned int count = 0;
	List pnode = *plist;     //Set the start of the linked list

	while (pnode) {
		++count;
		pnode = pnode->next; //Set the next node
	}

	return count;
}

//Create a node that stores the item and add it to the end of the linked list pointed to by plist (slower implementation)
bool AddItem(Item item, List *plist) {
	List pnew = (List)malloc(sizeof(Node));

	if (!pnew)
		return false;          //Exit function on failure

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (*plist) {
		List scan = *plist;
		while (scan->next)
			scan = scan->next; //Find the end of the list
		scan->next = pnew;     //Add pnew to the end of the list
	} else                     //Empty linked list,
		*plist = pnew;         //so put pnew at the beginning of the linked list

	return true;
}

//Access each node and execute the function pointed to by pfun
void Traverse(const List *plist, void(*pfun)(Item item)) {
	List pnode = *plist; //Set the start of the linked list

	while (pnode) {
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}

//Free memory allocated by malloc()
//Set the linked list pointer to NULL
void EmptyTheList(List *plist) {
	List psave;

	while (*plist) {
		psave = (*plist)->next; //Save the address of the next node
		free(*plist);           //Release the current node
		*plist = psave;         //Advance to the next node
	}
}

//Local function definition
//Copy an item to the node
void CopyToNode(Item item, Node *pnode) {
	pnode->item = item; //Copy structure
}
