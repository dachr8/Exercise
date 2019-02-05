#include<stdio.h>
//判断各位中是否有0
int main(void)
{
    int num,x=1;
    scanf("%d",&num);
    while(x!=0&&num>9)
    {
        x=num%10;
        num/=10;
    }
    if(x==0||num==0)
        printf("YES");
    else
        printf("NO");

    return 0;
}
