//invert4.c -- Display binary using bit operations

#include <stdio.h>
#include <limits.h>

char *itobs(int n, char *ps);
void show_bstr(const char *str);
int invert_end(int num, int bits);

int main(void) {
	char bin_str[CHAR_BIT * sizeof(int) + 1];
	int number;

	puts("Enter integers and see them in binary.");
	puts("Non-numeric input terminates program.");
	while (scanf("%d", &number) == 1) {
		printf("%d is\n", number);
		show_bstr(itobs(number, bin_str));
		putchar('\n');

		puts("Inverting the last 4 bits gives");
		show_bstr(itobs(invert_end(number, 4), bin_str));
		putchar('\n');
	}
	puts("Bye!");

	return 0;
}

char *itobs(int n, char *ps) {
	const static int size = CHAR_BIT * sizeof(int);

	for (int i = size - 1; i >= 0; --i, n >>= 1) //Move all bits in n one position to the right
		ps[i] = (1 & n) + '0'; //The value of the last digit of n
	ps[size] = '\0';
	return ps;
}

void show_bstr(const char *str) {
	for (int i = 0; str[i]; ++i) {
		putchar(str[i]);
		if (!((i + 1) % 4))
			putchar(' ');
	}
}

int invert_end(int num, int bits) {
	int mask = 0;
	for (int bitval = 1; bits > 0; --bits) {
		mask |= bitval;
		bitval <<= 1;
	}
	return num ^ mask;
}
