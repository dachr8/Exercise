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

extern int lineCount;       // 行数
extern int charCount;       // 字符数
extern int keywordCount;    // 关键字数
extern int identifierCount; // 标识符数
extern int numberCount;     // 常数
extern int letterCount;     // 字符数
extern int stringCount;     // 字符串数
extern int operatorCount;   // 操作符数
extern int delimiterCount;  // 界符数
