//films3.c -- Linked list using abstract data type (ADT) style
//Compile with list.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void showmovies(Item item);
char *s_gets(char *st, int n);

int main(void) {
	List movies;
	Item tmp;

	//initialization
	InitializeList(&movies);
	if (ListIsFull()) {
		fprintf(stderr, "No memory available! Bye!\n");
		exit(1);
	}

	//Get user input and save
	puts("Enter first movie title:");
	while (s_gets(tmp.title, TSIZE) && tmp.title[0] != '\0') {
		puts("Enter your rating <0-10>:");
		scanf("%d", &tmp.rating);
		while (getchar() != '\n')
			continue;
		if (!AddItem(tmp, &movies)) {
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		if (ListIsFull()) {
			puts("The list is now full.");
			break;
		}
		puts("Enter next movie title (empty line to stop):");
	}

	//display
	if (ListIsFull())
		puts("No data entered.");
	else {
		puts("Here is the movie list:");
		Traverse(&movies, showmovies);
	}
	printf("You entered %d movies.\n", ListItemCount(&movies));

	//Clean up
	EmptyTheList(&movies);
	puts("Bye!");

	return 0;
}

void showmovies(Item item) {
	printf("Mocie: %s Rating: %d\n", item.title, item.rating);
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
