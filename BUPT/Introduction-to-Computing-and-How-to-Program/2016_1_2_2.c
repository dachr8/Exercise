#include <stdio.h>

int main(void)
{
    int input;
    scanf("%d",&input);
    while(input!=-1)
    {
        if(input%3==1&&input%4==1)
            printf("%d ",input);
        scanf("%d",&input);
    }
    printf("-1\n");
    return 0;
}
