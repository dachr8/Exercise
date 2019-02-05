#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Head and tail linked list generalized list storage representation
typedef char atomType;
typedef enum {
	ATOM, LIST
}ElemTag;
typedef struct GLNode {
	ElemTag tag;       // Common part for distinguishing atomic nodes from list nodes
	union {            // Joint part of atomic node and list node
		atomType atom; // Atom is the value range of the atomic node, and atomType is defined by the user.
		struct {
			struct GLNode *hp, *tp;
		}ptr;          // ptr is the pointer field of the table node, hp and tp point to the header and footer respectively
	};
}*GList;               // Generalized list type