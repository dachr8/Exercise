//pe17-5b.c -- stack operations

#include <stdio.h>
#include <stdlib.h>
#include "pe17-5.h"

void InitializeStack(Stack *ps) {
	ps->top = 0;
}

bool FullStack(const Stack *ps) {
	return ps->top == MAXSTACK;
}

bool EmptyStack(const Stack *ps) {
	return ps->top == 0;
}

bool Push(Item item, Stack *ps) {
	if (ps->top == MAXSTACK)
		return false;
	else {
		ps->items[ps->top++] = item;
		return true;
	}
}

bool Pop(Item *pitem, Stack *ps) {
	if (ps->top) {
		ps->top--;
		*pitem = ps->items[ps->top];
		return true;
	} else
		return false;
}
