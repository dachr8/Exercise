#include <stdio.h>
#include <limits.h>

unsigned int rotate_l(unsigned int n, unsigned int b);
char *itobs(int n, char *ps);


int main(int argc, char *argv[]) {
	unsigned int val, rot, places;
	char bstr1[CHAR_BIT * sizeof(int) + 1], bstr2[CHAR_BIT * sizeof(int) + 1];

	printf("Enter an integer (q to quit): ");
	while (scanf("%ud", &val)) {
		puts("Enter the number of bits to be rotated:");
		if (scanf("%ul", &places) != 1)
			break;
		rot = rotate_l(val, places);
		itobs(val, bstr1);
		itobs(rot, bstr2);
		printf("%u rotated is %u.\n", val, rot);
		printf("%s rotated is %s.\n", bstr1, bstr2);
		printf("Next value: ");
	}

	puts("Done");

	return 0;
}

unsigned int rotate_l(unsigned int n, unsigned int b) {
	static const int size = CHAR_BIT * sizeof(int);

	b %= size; //keep b a valid value

	return (n << b) | (unsigned int)(n >> (size - b));
}

char *itobs(int n, char *ps) {
	const static int size = CHAR_BIT * sizeof(int);

	for (int i = size - 1; i >= 0; --i, n >>= 1) //Move all bits in n one position to the right
		ps[i] = (1 & n) + '0'; //The value of the last digit of n
	ps[size] = '\0';

	return ps;
}
