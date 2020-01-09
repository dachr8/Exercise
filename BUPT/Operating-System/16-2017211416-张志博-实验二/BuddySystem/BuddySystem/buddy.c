#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "buddy.h"

static inline int left_child(int index) {
	/* index * 2 + 1 */
	return ((index << 1) + 1);
}

static inline int right_child(int index) {
	/* index * 2 + 2 */
	return ((index << 1) + 2);
}

static inline int parent(int index) {
	/* (index+1)/2 - 1 */
	return (((index + 1) >> 1) - 1);
}

static inline bool is_power_of_2(int index) {
	return !(index & (index - 1));
}

/* a wrapper for malloc */
static void* d_malloc(size_t size) {
	void* tmp = NULL;

	tmp = malloc(size);
	if (tmp == NULL) {
		fprintf(stderr, "my_malloc: not enough memory, quit\n");
		exit(EXIT_FAILURE);
	}

	return tmp;
}

/* a wrapper for free */
static void d_free(void* addr) {
	free(addr);
}

static inline unsigned next_power_of_2(unsigned size) {
	/* depend on the fact that size < 2^32 */
	size -= 1;
	size |= (size >> 1);
	size |= (size >> 2);
	size |= (size >> 4);
	size |= (size >> 8);
	size |= (size >> 16);
	return size + 1;
}

/** allocate a new buddy structure
 * @param num_of_fragments number of fragments of the memory to be managed
 * @return pointer to the allocated buddy structure */
Buddy* buddy_new(unsigned num_of_fragments) {
	Buddy* self = NULL;

	if (num_of_fragments < 1 || !is_power_of_2(num_of_fragments)) {
		return NULL;
	}

	/* alloacte an array to represent a complete binary tree */
	self = (Buddy*)d_malloc(sizeof(Buddy) + 2 * num_of_fragments * sizeof(size_t));
	self->size = num_of_fragments;
	size_t node_size = num_of_fragments * 2;

	/* initialize *longest* array for buddy structure */
	int iter_end = num_of_fragments * 2 - 1;
	for (int i = 0; i < iter_end; i++) {
		if (is_power_of_2(i + 1)) {
			node_size >>= 1;
		}
		self->longest[i] = node_size;
	}

	return self;
}

/* choose the child with smaller longest value which is still larger
 * than *size* */
unsigned choose_better_child(Buddy* self, unsigned index, size_t size) {
	struct compound {
		size_t size;
		unsigned index;
	} children[2];
	children[0].index = left_child(index);
	children[0].size = self->longest[children[0].index];
	children[1].index = right_child(index);
	children[1].size = self->longest[children[1].index];

	int min_idx = (children[0].size <= children[1].size) ? 0 : 1;

	if (size > children[min_idx].size) {
		min_idx = 1 - min_idx;
	}

	return children[min_idx].index;
}

/** allocate *size* from a buddy system *self*
 * @return the offset from the beginning of memory to be managed */
int buddy_alloc(Buddy* self, size_t size) {
	if (self == NULL || self->size < size) {
		return -1;
	}
	size = next_power_of_2(size);

	unsigned index = 0;
	if (self->longest[index] < size) {
		return -1;
	}

	/* search recursively for the child */
	unsigned node_size = 0;
	for (node_size = self->size; node_size != size; node_size >>= 1) {
		/* choose the child with smaller longest value which is still larger than *size* */
		index = choose_better_child(self, index, size);
	}

	/* update the *longest* value back */
	self->longest[index] = 0;
	int offset = (index + 1) * node_size - self->size;

	while (index) {
		index = parent(index);
		self->longest[index] = max(self->longest[left_child(index)], self->longest[right_child(index)]);
	}

	return offset;
}

void buddy_free(Buddy* self, int offset) {
	if (self == NULL || offset < 0 || offset > self->size) {
		return;
	}

	/* get the corresponding index from offset */
	size_t node_size = 1;
	unsigned index = offset + self->size - 1;
	while (self->longest[index] != 0) {
		node_size <<= 1;    /* node_size *= 2; */
		if (index == 0) {
			break;
		}
		index = parent(index);
	}

	self->longest[index] = node_size;

	while (index) {
		index = parent(index);
		node_size <<= 1;

		size_t left_longest = self->longest[left_child(index)];
		size_t right_longest = self->longest[right_child(index)];

		if (left_longest + right_longest == node_size) {
			self->longest[index] = node_size;
		} else {
			self->longest[index] = max(left_longest, right_longest);
		}
	}
}

void buddy_print(Buddy* self) {
	int len = self->size << 1;
	char cs[] = {'/', '\\'};
	int idx = 0;

	for (int i = 0, max_col = len, level = 0; i < len - 1; ++i) {
		if (is_power_of_2(i + 1)) {
			max_col >>= 1;
			level++;
			idx = 0;
			printf("\n%d(%.2d): ", level, max_col);
		}
		printf("%*d", max_col, self->longest[i]);
	}

	for (int i = 0, max_col = len, level = 0; i < len - 1; ++i) {
		if (is_power_of_2(i + 1)) {
			max_col >>= 1;
			level++;
			idx = 0;
			printf("\n%d(%.2d): ", level, max_col);
		}
		char c;
		if (self->longest[i] > 0) {
			c = '-';
		} else {
			c = cs[idx];
			idx ^= 0x1;
		}

		for (int j = 0; j < max_col; ++j) {
			printf("%c", c);
		}
	}
	printf("\n");
}

int buddy_size(Buddy* self, int offset) {
	unsigned node_size = 1;
	unsigned index = offset + self->size - 1;

	while (self->longest[index]) {
		node_size >>= 1;
		index = parent(index);
	}

	return node_size;
}
