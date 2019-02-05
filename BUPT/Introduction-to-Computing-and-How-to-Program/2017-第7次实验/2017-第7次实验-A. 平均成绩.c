#include <stdio.h>
//2017-计算机导论与程序设计-第7次实验
//A. 平均成绩
int main(void)
{
    int n,sum=0,high=0,low=100;

    scanf("%d",&n);

    int a[n];

    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
        high=high>a[i]?high:a[i];
        low=low<a[i]?low:a[i];
    }
    printf("%.2lf %d %d",(double)sum/n,high,low);

    return 0;
}
