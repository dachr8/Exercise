#pragma warning(disable:4996)
#include "KeyList.h"
#include <iostream>
#include <algorithm>
#include <stack>


using namespace std;


KeyList::~KeyList() {
	for (int i = 0; i < 26; ++i)
		if (key[i] != NULL)
			destroyTree(key[i]);
}

int getHeight(NODE* t) {
	if (t == NULL)
		return 0;
	return t->height;
}

NODE* KeyList::LL_Rotate(NODE* t) {
	NODE* t2 = t->lchd;
	t->lchd = t2->rchd;
	t2->rchd = t;

	t->height = max(getHeight(t->lchd), getHeight(t->rchd)) + 1;
	t2->height = max(getHeight(t2->lchd), getHeight(t2->rchd)) + 1;

	return t2;
}

NODE* KeyList::RR_Rotate(NODE* t) {
	NODE* t2 = t->rchd;
	t->rchd = t2->lchd;
	t2->lchd = t;

	t->height = max(getHeight(t->lchd), getHeight(t->rchd)) + 1;
	t2->height = max(getHeight(t2->lchd), getHeight(t2->rchd)) + 1;

	return t2;
}

NODE* KeyList::LR_Rotate(NODE* t) {
	t->lchd = RR_Rotate(t->lchd);

	return LL_Rotate(t);
}

NODE* KeyList::RL_Rotate(NODE* t) {
	t->rchd = LL_Rotate(t->rchd);

	return RR_Rotate(t);
}

NODE* KeyList::addWord(char* s, NODE* tree, bool& isexist) {
	if (tree == NULL) {
		isexist = false;
		tree = (NODE*)malloc(sizeof(NODE));
		tree->lchd = tree->rchd = NULL;
		tree->height = 1;
		strcpy(tree->word, s);
		return tree;
	}
	if (strcmp(s, tree->word) < 0) {
		tree->lchd = addWord(s, tree->lchd, isexist);
		if (getHeight(tree->lchd) - getHeight(tree->rchd) == 2) {
			if (strcmp(s, tree->lchd->word) < 0)
				tree = LL_Rotate(tree);
			else
				tree = LR_Rotate(tree);
		}
	} else {
		if (strcmp(s, tree->word) > 0) {
			tree->rchd = addWord(s, tree->rchd, isexist);
			if (getHeight(tree->rchd) - getHeight(tree->lchd) == 2) {
				if (strcmp(s, tree->rchd->word) > 0)
					tree = RR_Rotate(tree);
				else
					tree = RL_Rotate(tree);
			}
		} else {
			isexist = true;
			return tree;
		}
	}

	tree->height = max(getHeight(tree->lchd), getHeight(tree->rchd)) + 1;
	return tree;
}

void KeyList::destroyTree(NODE* t) {
	if (t == NULL)
		return;
	if (t->lchd == NULL && t->rchd == NULL) {
		free(t);
		return;
	}
	destroyTree(t->lchd);
	destroyTree(t->rchd);
}

void KeyList::printSelf(NODE* t) {
	if (t == NULL)
		return;
	cout << t->word << " lchd:";
	if (t->lchd)
		cout << t->lchd->word << " rchd:";
	else
		cout << " rchd:";
	if (t->rchd)
		cout << t->rchd->word << endl;
	else
		cout << endl;

	printSelf(t->lchd);
	printSelf(t->rchd);
}

void KeyList::printTree(int n) {
	printSelf(key[n]);
}

bool KeyList::add(char* s) {
	bool ans;
	key[s[0] - 'a'] = addWord(s, key[s[0] - 'a'], ans);
	return ans;
}

NODE* KeyList::getKey(const char* s) {
	NODE* t = key[s[0] - 'a'];
	if (t == NULL)
		return NULL;
	while (t != NULL) {
		int cmp = strcmp(s, t->word);
		if (cmp < 0)
			t = t->lchd;
		else {
			if (cmp > 0)
				t = t->rchd;
			else
				return t;
		}
	}
	return NULL;
}

void KeyList::initializeFromFile(char* s) {
	FILE* f = fopen(s, "r+");
	char word[10];
	int type;
	bool isexist;
	while (fscanf(f, "%s %d", word, &type) != EOF) {
		key[word[0] - 'a'] = addWord(word, key[word[0] - 'a'], isexist);
	}
	fclose(f);
}
