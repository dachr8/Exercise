#include<stdio.h>
int main(void)
{
    int sum=0;
    char input;
    scanf("%c",&input);
    if(input!='0')
    {
        while(input!='0')
        {
            sum=sum*10+input-'0';
            scanf("%c",&input);
        }
        scanf("%c",&input);
        while(input!='\n')
        {
            sum=sum*10+input-'0';
            scanf("%c",&input);
        }
    }
    else
        scanf("%d",&sum);
    printf("%d",sum);

    return 0;
}

