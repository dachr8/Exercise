//petclub.c -- Use binary search number

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

char menu(void);
void addpet(Tree *pt);
void droppet(Tree *pt);
void showpets(const Tree *pt);
void findpet(const Tree *pt);
void printitem(Item item);
void uppercase(char *str);
char *s_gets(char *st, int n);

int main(void) {
	Tree pets;
	char choice;

	InitializeTree(&pets);
	while ((choice = menu()) != 'q')
		switch (choice) {
			case 'a':
				addpet(&pets);
				break;
			case 'l':
				showpets(&pets);
				break;
			case 'f':
				findpet(&pets);
				break;
			case 'n':
				printf("%d pets in club\n", TreeItemCount(&pets));
				break;
			case 'd':
				droppet(&pets);
				break;
			default:
				puts("Switching error");
				break;
		}
	DeleteAll(&pets);
	puts("Bye.");

	return 0;
}

char menu(void) {
	int ch;
	bool menu = false;

	puts("Nerfville Pet Club Menbership Program");
	puts("Enter the letter corresponding to your choice:");
	puts("a) add a pet       l) show list of pets");
	puts("n) number of pets  f) find pets");
	puts("d) delete a pet    q) quit");
	while (!menu && (ch = getchar()) != EOF) {
		while (getchar() != '\n') //Handling the rest of the input line
			continue;
		ch = tolower(ch);
		if (strchr("alrfndq", ch))
			menu = true;
		else
			puts("Please enter an a, l, f, n, d, or q:");
	}
	if (ch == EOF)
		ch = 'q';

	return ch;
}

void addpet(Tree *pt) {
	Item tmp;

	if (TreeIsFull(pt))
		puts("No room in the club!");
	else {
		puts("Please enter name of pet:");
		s_gets(tmp.petname, SLEN);
		puts("Please enter pet kind:");
		s_gets(tmp.petkind, SLEN);
		uppercase(tmp.petname);
		uppercase(tmp.petkind);
		AddItem(&tmp, pt);
	}
}

void showpets(const Tree *pt) {
	if (TreeIsEmpty(pt))
		puts("No entries!");
	else
		Traverse(pt, printitem);
}

void printitem(Item item) {
	printf("Pet: %-19s Kind: %-19s\n", item.petname, item.petkind);
}

void findpet(const Tree *pt) {
	Item tmp;

	if (TreeIsEmpty(pt)) {
		puts("No entries!");
		return;
	}

	puts("Please enter name of pet you wish to find:");
	s_gets(tmp.petname, SLEN);
	puts("Please enter pet kind:");
	s_gets(tmp.petkind, SLEN);
	uppercase(tmp.petname);
	uppercase(tmp.petkind);
	printf("%s the %s ", tmp.petname, tmp.petkind);
	if (InTree(&tmp, pt))
		puts("is a member.");
	else
		puts("is not a member.");
}

void droppet(Tree *pt) {
	Item tmp;
	
	if (TreeIsEmpty(pt)) {
		puts("No entries!");
		return;
	}

	puts("Please enter name of pet you wish to delete:");
	s_gets(tmp.petname, SLEN);
	puts("Please enter pet kind:");
	s_gets(tmp.petkind, SLEN);
	uppercase(tmp.petname);
	uppercase(tmp.petkind);
	printf("%s the %s ", tmp.petname, tmp.petkind);
	if (DeleteItem(&tmp, pt))
		puts("is dropped from the club.");
	else
		puts("is not a member.");
}

void uppercase(char *str) {
	while (*str) {
		*str = toupper(*str);
		++str;
	}
}

char *s_gets(char *st, int n) {
	char *ret_val, *find;

	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		if ((find = strchr(st, '\n')))
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}
