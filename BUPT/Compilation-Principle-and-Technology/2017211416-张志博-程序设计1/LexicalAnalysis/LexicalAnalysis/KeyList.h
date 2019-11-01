#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>


typedef struct node {
	char word[10];
	int height;// The depth of the node
	struct node* lchd;
	struct node* rchd;
}NODE;


class KeyList {
private:
	NODE* key[26] = {0};
	NODE* LL_Rotate(NODE* t);
	NODE* RR_Rotate(NODE* t);
	NODE* LR_Rotate(NODE* t);
	NODE* RL_Rotate(NODE* t);
	NODE* addWord(char* s, NODE* tree, bool& isexist);
	void destroyTree(NODE* t);
	void printSelf(NODE* t);
public:
	KeyList() {
	};
	~KeyList();
	void initializeFromFile(char* s);
	bool add(char* s);
	void printTree(int n);
	NODE* getKey(const char* s);
};