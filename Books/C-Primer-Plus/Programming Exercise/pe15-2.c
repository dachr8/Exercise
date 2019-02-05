#include <stdio.h>
#include <stdlib.h>

int bstr_to_dec(const char *str);
char *itobs(int n, char *ps);


int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s binarynum1 binarynun2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int v1 = bstr_to_dec(argv[1]), v2 = bstr_to_dec(argv[2]);
	char bstr[8 * sizeof(int) + 1];

	printf("~%s = %s\n", argv[1], itobs(~v1, bstr));
	printf("~%s = %s\n", argv[2], itobs(~v2, bstr));
	printf("%s & %s = %s\n", argv[1], argv[2], itobs(v1 & v2, bstr));
	printf("%s | %s = %s\n", argv[1], argv[2], itobs(v1 | v2, bstr));
	printf("%s ^ %s = %s\n", argv[1], argv[2], itobs(v1 ^ v2, bstr));

	puts("Done");

	return 0;
}

int bstr_to_dec(const char *str) {
	int val = 0;

	while (*str != '\0')
		val = 2 * val - '0' + *str++;

	return val;
}

char *itobs(int n, char *ps) {
	const static int size = CHAR_BIT * sizeof(int);

	for (int i = size - 1; i >= 0; --i, n >>= 1) //Move all bits in n one position to the right
		ps[i] = (1 & n) + '0'; //The value of the last digit of n
	ps[size] = '\0';

	return ps;
}
