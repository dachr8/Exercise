#include<stdio.h>

int main(void)
{
    char ch;

    scanf("%c",&ch);
    while(ch!='\n')
    {
        if('a'<=ch&&ch<='z')
            ch+='A'-'a';
        else if('A'<=ch&&ch<='Z')
            ch='A'+'Z'-ch;
        else if('0'<=ch&&ch<='6')
            ch+=3;
        else if('7'<=ch&&ch<='9')
            ch-=7;
        printf("%c",ch);
        scanf("%c",&ch);
    }

    return 0;
}
