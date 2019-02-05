#include <stdio.h>
//2017-计算机导论与程序设计-第7次实验
//C. 奇数偶数
int main(void)
{
    int n;

    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    for(int i=0;i<n;i++)
        if(a[i]%2==0)
            for(int j=i,tmp;j>0&&a[j-1]%2;j--)
            {
                tmp=a[j-1];
                a[j-1]=a[j];
                a[j]=tmp;
            }

    for(int i=0;i<n;i++)
        printf("%d%c",a[i],i+1-n?' ':'\n');

    return 0;
}
