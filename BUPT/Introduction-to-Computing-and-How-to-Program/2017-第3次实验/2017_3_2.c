#include <stdio.h>
//输入格式：输入三个正整数a、b、c。
//a、b代表所求区间范围，满足1<=a<=b<=10000，c代表限制条件，c>=0。
//输出格式：输出满足条件的整数，每五个数为一行，整数之间用tab分隔，最后一个数后为换行符。
//当该区间没有符合条件的整数时，输出“There is no proper number in the interval.” 
int main(void)
{
    int a,b,c,x,len=0,ax;
    scanf("%d%d%d",&a,&b,&c);
    for(;a<=b;a++)
    {
        x=0;
        for(int i=1;i<a;i++)
        {
            if(a%i==0)
                x+=i;
        }
        ax=a-x>0?a-x:x-a;
        if(ax<=c)
        {
            len++;
            if((len-1)%5!=0&&len!=1)
                printf("\t");
            else if(len!=1)
                printf("\n");
            printf("%d",a);
        }
    }
    if(len==0)
        printf("There is no proper number in the interval.");
    printf("\n");

    return 0;
}
