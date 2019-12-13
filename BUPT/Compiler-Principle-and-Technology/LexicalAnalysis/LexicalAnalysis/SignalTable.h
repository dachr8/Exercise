#pragma once
#include <iostream>
#include <string>
#include <cstring>


using namespace std;


constexpr auto UNKNOWN = 0;
constexpr auto VARIABLE = 1;
constexpr auto FUNCTION = 2;
constexpr auto STRUCTURE = 3;
constexpr auto CLASS = 4;
constexpr auto CONSTNUM = 5;
constexpr auto CONSTSTRING = 6;
constexpr auto CONSTCHAR = 7;


typedef struct signalNode {
	string s;
	int type;
	long long int pos;
	struct signalNode* next;
}SGLNode;


class SignalTable {
private:
	string name;
	SGLNode* table[27] = {0};
public:
	~SignalTable();
	SignalTable();
	SignalTable(char* filename);
	void setName(char* s);
	int addElement(string s, int type);
	int hasElement(string s);
	void store(char* filename);
};
