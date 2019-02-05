//ifdef.c -- Conditional compilation

#include <stdio.h>

#define JUST_CHECKING
#define LIMIT 4


int main(void) {
	int total = 0;

	for (int i = 1; i <= LIMIT; ++i) {
		total += 2 * i*i + 1;
#ifdef JUST_CHECKING
		printf("i = %d, running total = %d\n", i, total);
#endif
	}
	printf("Grand total = %d\n", total);

	return 0;
}
