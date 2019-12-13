#pragma once

#include "KeyList.h"
#include "SignalTable.h"

constexpr auto Q0 = 0;
constexpr auto Q1 = 1;
constexpr auto Q2 = 2;
constexpr auto Q3 = 3;
constexpr auto Q4 = 4;
constexpr auto Q5 = 5;
constexpr auto Q6 = 6;

constexpr auto BUFFERLEN = 4001;

extern KeyList keylist;
extern SignalTable signalTable;

extern char buffer[2][BUFFERLEN];

extern bool currentBufferm, forwardBuffer;
extern char* curPt, * forwardPt;
extern FILE* sourcePointer, * targetPointer, * errorListPointer;

extern int lineCount;       // ����
extern int charCount;       // �ַ���
extern int keywordCount;    // �ؼ�����
extern int identifierCount; // ��ʶ����
extern int numberCount;     // ����
extern int letterCount;     // �ַ���
extern int stringCount;     // �ַ�����
extern int operatorCount;   // ��������
extern int delimiterCount;  // �����
