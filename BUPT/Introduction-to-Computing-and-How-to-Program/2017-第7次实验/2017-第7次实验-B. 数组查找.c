#include <stdio.h>
//2017-计算机导论与程序设计-第7次实验
//B. 数组查找
int main(void)
{
    int n,m,found;

    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    scanf("%d",&m);
    int b[m];
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);

    for(int j=0;j<m;j++)
    {
        found=0;
        for(int i=0;i<n&&!found;i++)
            if(b[j]==a[i]&&n>1)
            {
                if(!i)
                    printf("%d\n",a[i+1]);
                else if(i==n-1)
                    printf("%d\n",a[i-1]);
                else
                    printf("%d %d\n",a[i-1],a[i+1]);
                found=1;
            }
        if(!found)
            printf("NULL\n");
    }

    return 0;
}
