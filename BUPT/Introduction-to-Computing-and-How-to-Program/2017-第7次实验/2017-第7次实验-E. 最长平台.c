#include <stdio.h>
//2017-计算机导论与程序设计-第7次实验
//D. 最长平台
int main(void)
{
    int n,sum=1,maxSum=1,a,b=0;

    scanf("%d",&n);
    for (int i=0;i<n;i++)
    {
        scanf("%d",&a);
        if(a==b&&i>0)
            sum++;
        else
            sum=1;
        maxSum=maxSum>sum?maxSum:sum;
        b=a;
    }
    printf("%d",maxSum);

    return 0;
}
