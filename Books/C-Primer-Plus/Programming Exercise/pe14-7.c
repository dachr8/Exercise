//booksave.c -- Save the contents of the structure in the file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 10 //maximum number of books

typedef struct book { //set up book template
	char title[MAXTITL], author[MAXAUTL];
	float value;
} BOOK;

typedef struct pack {
	BOOK book; //different namespaces for two book identifiers
	bool delete_me;
}PACK;

/*
strategy: rather than rearrange array of structures every time
there is a deletion, combine structure with a data member indicating
whether or not an item is marked for deletion. At the end of the program,
show and store only those items not marked for deletion. The deletion
information could be stored in a separate array, but storing it in a
structure along with the book structure keeps the information together.
*/

char *s_gets(char *st, int n);
int getlet(const char *s);
int getbook(PACK *pb);
void update(PACK *item);

int main(void) {
	PACK library[MAXBKS]; //array of structures
	FILE *pbooks;
	int count = 0, deleted = 0;

	if ((pbooks = fopen("book.dat", "r")) != NULL) {
		while (count < MAXBKS && fread(&library[count], sizeof(BOOK), 1, pbooks) == 1) {
			if (!count)
				puts("Current contents of book.dat:");
			printf("%s by %s: $%.2f\n", library[count].book.title,
				library[count].book.author, library[count].book.value);
			printf("Do you wish to change or delete this entry?<y/n> ");
			if (getlet("yn") == 'y') {
				printf("Enter c to change, d to delete entry: ");
				if (getlet("cd") == 'd') {
					library[count].delete_me = true;
					++deleted;
					puts("Entry marked for deletion.");
				} else
					update(&library[count]);
			}
			++count;
		}
		fclose(pbooks);
	}

	int filecount = count - deleted;
	if (count == MAXBKS) {
		fputs("The book.dat file is full.", stderr);
		exit(EXIT_FAILURE);
	}
	puts("Please add new book titles.");
	puts("Press [enter] at the start of a line to stop.");

	int open = 0;
	while (filecount < MAXBKS) {
		if (filecount < count) {
			while (!library[open].delete_me)
				++open;
			if (getbook(&library[open]))
				break;
		} else if (getbook(&library[filecount]))
			break;
		++filecount;
		if (filecount < MAXBKS)
			puts("Enter the next book title.");
	}
	puts("Here is the list of your books:");
	for (int i = 0; i < filecount; ++i)
		if (!library[i].delete_me)
			printf("%s by %s: $%.2f\n", library[i].book.title,
				library[i].book.author, library[i].book.value);
	if (!(pbooks = fopen("book.dat", "w"))) {
		fputs("Can't open book.dat file for output\n", stderr);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < filecount; ++i)
		if (!library[i].delete_me)
			fwrite(&(library[i].book), sizeof(BOOK), 1, pbooks);
	fclose(pbooks);
	puts("Done!");

	return 0;
}

char *s_gets(char *st, int n) {
	char *ret_val = fgets(st, n, stdin), *find;

	if (ret_val) {
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}

	return ret_val;
}

int getlet(const char * s) {
	char c = getchar();
	while (!strchr(s, c)) {
		printf("Enter a character in the list %s\n", s);
		while (getchar() != '\n')
			continue;
		c = getchar();
	}
	while (getchar() != '\n')
		continue;
	return c;
}

int getbook(struct pack * pb) {
	int status = 0;
	if (!s_gets(pb->book.title, MAXTITL) || pb->book.title[0] == '\0')
		status = 1;
	else {
		printf("Now enter the author: ");
		s_gets(pb->book.author, MAXAUTL);
		printf("Now enter the value: ");
		while (scanf("%f", &pb->book.value) != 1) {
			puts("Please use numeric input");
			scanf("%*s");
		}
		while (getchar() != '\n')
			continue; //clear input line
		pb->delete_me = false;
	}
	return status;
}

void update(PACK * item) {
	BOOK copy;
	char c;
	copy = item->book;

	puts("Enter the letter that indicates your choice:");
	puts("t) modify title a) modify author");
	puts("v) modify value s) quit, saving changes");
	puts("q) quit, ignore changes");
	while ((c = getlet("tavsq")) != 's' && c != 'q') {
		switch (c) {
			case 't': puts("Enter new title: ");
				s_gets(copy.title, MAXTITL);
				break;
			case 'a': puts("Enter new author: ");
				s_gets(copy.author, MAXAUTL);
				break;
			case 'v': puts("Enter new value: ");
				while (scanf("%f", &copy.value) != 1) {
					puts("Enter a numeric value: ");
					scanf("%*s");
				}
				while (getchar() != '\n')
					continue;
				break;
		}
		puts("t) modify title a) modify author");
		puts("v) modify value s) quit, saving changes");
		puts("q) quit, ignore changes");
	}
	if (c == 's')
		item->book = copy;
}
