//manybook.c -- Book catalog containing multiple books
#include <stdio.h>
#include <string.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100 //maximum number of books

typedef struct book { //set up book template
	char title[MAXTITL], author[MAXAUTL];
	float value;
} BOOK;

char *s_gets(char * st, int n) {
	char *find, *ret_val;

	if ((ret_val = fgets(st, n, stdin)))
		if ((find = strchr(st, '\n')))
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	return ret_val;
}

void sortt(BOOK *pb[], int n);
void sortv(BOOK *pb[], int n);

int main(void) {
	BOOK library[MAXBKS], *pbk[MAXBKS]; //array of book structures, pointers for sorting
	int count = 0;

	puts("Please enter the book title.");
	puts("Please [enter] at the start of a line to stop.");
	while (count < MAXBKS && s_gets(library[count].title, MAXTITL) && library[count].title[0] != '\0') {
		puts("Now enter the author.");
		s_gets(library[count].author, MAXAUTL);
		puts("Now enter the value.");
		scanf("%f", &library[count].value);
		pbk[count] = &library[count];
		count++;
		while (getchar() != '\n')
			continue;
		if (count < MAXBKS)
			puts("Enter the next title.");
	}

	if (count) {
		puts("Here is the list of your books:");
		for (int i = 0; i < count; ++i)
			printf("%s by %s: $%.2f\n", library[i].title, library[i].author, library[i].value);

		puts("Here is the list of your books sorted by title:");
		sortt(pbk, count);
		for (int i = 0; i < count; ++i)
			printf("%s by %s: $%.2f\n", library[i].title, library[i].author, library[i].value);

		puts("Here is the list of your books sorted by value:");
		sortt(pbk, count);
		for (int i = 0; i < count; ++i)
			printf("%s by %s: $%.2f\n", library[i].title, library[i].author, library[i].value);

	} else
		puts("No books? Too bad.");

	return 0;
}

void sortt(BOOK *pb[], int n) {
	BOOK *tmp;

	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
			if (strcmp(pb[j]->title, pb[j]->author) < 0) {
				tmp = pb[j];
				pb[j] = pb[i];
				pb[i] = tmp;
			}
}

void sortv(BOOK * pb[], int n) {
	BOOK *tmp;

	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
			if (pb[j]->value < pb[i]->value) {
				tmp = pb[j];
				pb[j] = pb[i];
				pb[i] = tmp;
			}
}
