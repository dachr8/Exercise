#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Sequential binary tree storage representation
#define MAXSIZE 100                 // The maximum number of nodes in the binary tree
typedef char elemType;
typedef elemType SqBiTree[MAXSIZE]; // Unit 0 stores the root node