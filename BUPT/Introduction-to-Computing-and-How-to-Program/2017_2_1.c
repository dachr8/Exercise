#include<stdio.h>

int main(void)
{
    int input=0,min=0,max=0,tmp;

    while(min<=0)
        scanf("%d",&min);
    while(input<=0)
        scanf("%d",&input);
    tmp=min;
    min=min>input?input:min;
    input=tmp>input?tmp:input;
    while(input!=0)
    {
        min=min>input?input:min;
        max=max>input?max:input;
        tmp=input;
        scanf("%d",&input);
        if(input<0)
            input=tmp;
    }
    printf("%d",max-min);

    return 0;
}
