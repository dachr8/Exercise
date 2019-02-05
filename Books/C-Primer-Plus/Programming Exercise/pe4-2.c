#include <stdio.h>
#include <string.h>
//Programming Exercise 4-2
//Prompt user to enter first name and last name
int main(void)
{
    char fname[40];
    char lname[40];

    printf("Enter your first name: ");
    scanf("%s",fname);
    printf("Enter your last name: ");
    scanf("%s",lname);
    printf("\"%s %s\"\n",fname,lname);
    printf("\"%20s %s\"\n",fname,lname);
    printf("\"%s %-20s\"\n",fname,lname);
    printf("%*s %s\n",strlen(fname)+3,fname,lname);

    return 0;
}
