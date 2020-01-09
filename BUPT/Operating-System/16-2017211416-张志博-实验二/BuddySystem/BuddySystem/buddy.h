#pragma once
#include <stdio.h>

typedef struct Buddy {
	size_t size;
	size_t longest[1];
}Buddy;

Buddy* buddy_new(unsigned num_of_fragments);
int buddy_alloc(Buddy* self, size_t size);
void buddy_free(Buddy* self, int offset);
void buddy_print(Buddy* self);
int buddy_size(Buddy* self, int offset);