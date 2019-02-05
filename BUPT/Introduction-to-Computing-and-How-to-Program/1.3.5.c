#include <stdio.h>
//第3题. 实验手册中实验3的第5题（循环嵌套选择）
int main(void)
{
    int n,sum;
    printf("Please input an integer:");
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        if(i%21==0)
            sum+=i;
    }
    printf("The result is:%d",sum*sum);
    return 0;
}
