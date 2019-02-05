#include <stdio.h>
#include <limits.h>

char *itobs(int n, char *ps);
int onbits(int n);


int main(int argc, char *argv[]) {
	int val;
	char bstr[CHAR_BIT * sizeof(int) + 1];

	printf("Enter an integer (q to quit): ");
	while (scanf("%d", &val)) {
		printf("%d (%s) has %d bit(s) on.\n",val,itobs(val,bstr),onbits(val));
		printf("Next value: ");
	}

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

int onbits(int n) {
	static const int size = CHAR_BIT * sizeof(int);
	int ct = 0;
	
	for (int i = 0; i < size; ++i, n >>= 1)
		if ((1 & n) == 1)
			++ct;
	
	return ct;
}
