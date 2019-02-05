#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ASIZE 128 // ASCII
#define PATTERN_LEN 99

// String heap sequential storage structure
typedef struct {
	int length;   // Current length of the string
	char ch[0];   // If it is a non - empty string, the storage area is allocated according to the length of the string, otherwise ch is NULL.
}TString;

// String fixed length storage structure
typedef struct {
	int length;             // Current length of the string
	char ch[PATTERN_LEN];   // One-dimensional array of storage strings
}SString;

// Parameter: text(English document)
// First, read an English word that the user wants to retrieve.
// Then, retrieve the English word in the English document, and output the number of occurrences and all positions of the English word.
// Return false if the English word is empty, otherwise return true.
// Added: wildcard characters are included in the input words
bool keywordSearch_BM(TString *text, SString pattern);