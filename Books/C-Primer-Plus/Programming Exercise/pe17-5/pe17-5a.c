#include <stdio.h>
#include <string.h>
#include "pe17-5.h"

#define SLEN 81

char *s_gets(char *st, int n);


int main(void) {
	Stack stch;
	char tmp[SLEN], ch;
	int i;

	InitializeStack(&stch);
	puts("Enter a line (an empty line to quit):");
	while (s_gets(tmp, SLEN) && tmp[0] != '\0') {
		i = 0;
		while (tmp[i] != '\0' && !FullStack(&stch))
			Push(tmp[i++], &stch);
		while (!EmptyStack(&stch)) {
			Pop(&ch, &stch);
			putchar(ch);
		}
		printf("\nEnter next line (empty line to quit): ");
	}
	puts("Done!");

	return 0;
}

char *s_gets(char *st, int n) {
	char *ret_val = fgets(st, n, stdin), *find;

	if (ret_val) {
		find = strchr(st, '\n'); // look for newline
		if (find)                // if the address is not NULL,
			*find = '\0';        // place a null character there
		else
			while (getchar() != '\n')
				continue;        // dispose of rest of line
	}
	return ret_val;
}
