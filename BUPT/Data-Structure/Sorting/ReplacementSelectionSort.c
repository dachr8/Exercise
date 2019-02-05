#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Memory work area storage structure
typedef char redType;
typedef int  keyType;
typedef struct rcdNode {
	redType rec;       // Record
	keyType key;       // Keywords extracted from the record
	int rnum;          // The segment number of the merged segment
}rcdNode, workArea[w]; // Memory work area, capacity is w