#include<stdio.h>

int main(void)
{
    int sum=0,n=1;
    char input='*';

    while(input=='*')
        scanf("%c",&input);
    while(input!='\n')
    {
        sum+=(input-'0')*n;
        scanf("%c",&input);
        while(input=='*')
            scanf("%c",&input);
        n*=10;
    }
    printf("%d",sum);

    return 0;
}
