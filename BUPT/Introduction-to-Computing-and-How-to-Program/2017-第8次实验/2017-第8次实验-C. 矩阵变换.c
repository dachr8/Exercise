#include <stdio.h>
//2017-计算机导论与程序设计-第8次实验
//C. 矩阵变换
int main(void)
{
    int n,tmp,found=1;

    scanf("%d",&n);

    int a[n][n],sum[n];

    for(int i=0;i<n;i++)
    {
        sum[i]=0;
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
            sum[i]+=a[i][j];
        }
    }
    while(found)
    {
        found=0;
        for(int i=0;i<n-1;i++)
            if(sum[i]>sum[i+1])
            {
                for(int j=0;j<n;j++)
                {
                    tmp=a[i][j];
                    a[i][j]=a[i+1][j];
                    a[i+1][j]=tmp;
                }
                tmp=sum[i];
                sum[i]=sum[i+1];
                sum[i+1]=tmp;
                found=1;
            }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
            printf("%d ",a[i][j]);
        printf("%d\n",a[i][n-1]);
    }

    return 0;
}
