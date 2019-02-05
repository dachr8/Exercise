#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Binary list (child-brother) tree storage representation
typedef char elemType;
typedef struct CSNode {
	elemType data;
	struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;