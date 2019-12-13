#pragma warning(disable:4996)
#include "SignalTable.h"
#include <cstdio>
#include <fstream>


SignalTable::SignalTable() {
	SGLNode* tmp = NULL;
	for (int i = 0; i < 27; i++) {
		tmp = new SGLNode();
		tmp->next = NULL;
		table[i] = tmp;
	}
}

SignalTable::SignalTable(char* filename) {
	string s;
	int type;

	ifstream in(filename);
	streambuf* stdcin = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	while (cin >> s >> type)
		addElement(s, type);

	cin.rdbuf(stdcin);
}

SignalTable::~SignalTable() {
	FILE* f = fopen(name.c_str(), "w+");
	if (f) {
		SGLNode* ptr, * lst;
		for (int i = 0; i < 27; ++i) {
			ptr = table[i];
			bool first = true;
			do {
				if (!first)
					fprintf(f, "%s %lld\n", ptr->s.c_str(), ptr->pos);
				first = false;
				lst = ptr;
				ptr = ptr->next;
				delete lst;
			} while (ptr != NULL);
		}
		fclose(f);
	}
}


int tellCapital(string s) {
	if (s[0] == '_')
		return 26;
	if (s[0] >= 'A' && s[0] <= 'Z')
		s[0] = s[0] + 32;
	return s[0] - 'a';
}


void SignalTable::store(char* filename) {
	FILE* f = fopen(filename, "w+");
	for (int i = 0; i < 27; i++) {
		SGLNode* ptr = table[i]->next;
		while (ptr != NULL) {
			fprintf(f, "%s %d %lld\n", ptr->s.c_str(), ptr->type, ptr->pos);
			ptr = ptr->next;
		}
	}
	fclose(f);
}


int SignalTable::addElement(string s, int type) {
	int index = tellCapital(s);

	if (index < 0 || index>26)
		return -1;

	SGLNode* ptr = table[index];
	int cnt = 0;
	while (ptr->next != NULL) {
		ptr = ptr->next;
		cnt++;
	}
	SGLNode* tmp = new SGLNode();
	tmp->next = NULL;
	tmp->s.assign(s);
	tmp->type = type;
	tmp->pos = cnt;
	ptr->next = tmp;

	return cnt;
}

int SignalTable::hasElement(string s) {
	int index = tellCapital(s);
	if (index < 0 || index>26)
		return -1;

	SGLNode* ptr = table[index]->next;
	int cnt = 0;
	while (ptr != NULL) {
		if (!strcmp(ptr->s.c_str(), s.c_str()))
			return cnt;
		ptr = ptr->next;
		cnt++;
	}
	return -1;
}

void SignalTable::setName(char* s) {
	name = "";
	while (*s != '.') {
		name.append(1, *s);
		s++;
	}
	name.append("_signalTable.txt");
}
