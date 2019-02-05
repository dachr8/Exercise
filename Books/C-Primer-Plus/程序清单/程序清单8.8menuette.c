#include <stdio.h>
//menuette.c--Menu program

void count(void);
char getChoice(void);
char getFirst(void);
int getInt(void);

int main(void)
{
    int choice;

    while ((choice=getChoice())!='q')
    {
        switch (choice)
        {
            case 'a':printf("Buy low, sell high.\n");
                break;
            case 'b':putchar('\a');
                break;
            case 'c':count();
                break;
            default:printf("Program error!\n");
                break;
        }
    }
    printf("Bye.\n");

    return 0;
}

void count(void)
{
    int n;

    printf("Count how far? Enter an integer:\n");
    n=getInt();
    for (int i = 1; i <= n; ++i)
        printf("%d\n",i);
    while (getchar()!='\n')
        continue;
}

char getChoice(void)
{
    char ch;

    printf("Enter the letter of your choice:\n");
    printf("a. advice         b.bell\n");
    printf("c. count          d.quit\n");
    ch=getFirst();
    while ((ch<'a'||ch>'c')&&ch!='q')
    {
        printf("Please respond with a, b, c, or q.\n");
        ch=getFirst();
    }

    return ch;
}

char getFirst(void)
{
    char ch;

    ch=(char)getchar();
    while (getchar()!='\n')
        continue;

    return ch;
}

int getInt(void)
{
    int input;
    char ch;

    while (scanf("%d",&input)!=1)
    {
        while ((ch=(char)getchar())!='\n')
            putchar(ch);
        printf(" is not an integer.\n");
        printf("Please enter an integer value, such as 23, -123, or 3: ");
    }

    return input;
}
