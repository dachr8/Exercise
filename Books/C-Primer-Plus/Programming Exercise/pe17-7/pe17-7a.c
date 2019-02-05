#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pe17-7.h"

#define SLEN 81

void printitem(Item item);
char menu(void);
void showwords(const Tree * pt);
void findword(const Tree * pt);
char *s_gets(char *st, int n);

int main(void) {
	Tree wordcount;
	FILE *fp;
	Item entry;
	char filename[SLEN], word[SLEN], choice;

	puts("Enter name of file to be processed:");
	s_gets(filename, SLEN);
	if (!(fp = fopen(filename, "r"))) {
		printf("Can't open file %s. Bye.\n", filename);
		exit(EXIT_FAILURE);
	}
	InitializeTree(&wordcount);
	while (fscanf(fp, "%s", word) == 1 && !TreeIsFull(&wordcount)) {
		strcpy(entry.wrd, word);
		AddItem(&entry, &wordcount);
	}
	while ((choice = menu()) != 'q') {
		switch (choice) {
			case 's':
				showwords(&wordcount);
				break;
			case 'f':
				findword(&wordcount);
				break;
			default:
				puts("Switching error");
				break;
		}
	}
	fclose(fp);
	puts("Done");

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

char menu(void) {
	int ch;
	bool menu = false;

	puts("Word counting program");
	puts("Enter the letter corresponding to your choice:");
	puts("s) show word list f) find a word");
	puts("q) quit");
	while (!menu && (ch = getchar()) != EOF) {
		while (getchar() != '\n') // discard rest of line
			continue;
		ch = tolower(ch);
		if (strchr("sfq", ch))
			menu = true;
		else
			puts("Please enter an s, f, or q:");
	}
	if (ch == EOF) // make EOF cause program to quit 
		ch = 'q';

	return ch;
}

void showwords(const Tree *pt) {
	if (TreeIsEmpty(pt))
		puts("No entries!");
	else
		Traverse(pt, printitem);
}

void findword(const Tree *pt) {
	char word[SLEN];
	Item entry;

	if (TreeIsEmpty(pt)) {
		puts("No entries!");
		return; // quit function if tree is empty
	}
	printf("Enter the word to find: ");
	scanf("%s", word);
	while (getchar() != '\n')
		continue;
	strcpy(entry.wrd, word);
	const Item *pi = WhereInTree(&entry, pt);
	if (pi)
		printf("%s appears %d times.\n", word, pi->count);
	else
		printf("%s is not in the list.\n", word);
}

void printitem(Item item) {
	printf("%3d: %s\n", item.count,item.wrd);
}
