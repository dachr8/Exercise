#include <stdio.h>
#include <stdlib.h>
//2017-计算机导论与程序设计-第9次实验
//D. 动态内存分配－Sub problem2

int **Create2(int n,int m);

int main(void)
{
    int n,m,**ptr;

    scanf("%d%d",&n,&m);

    ptr=Create2(n,m);

    for(int i=0;i<n;i++)
        for(int j=0,tmp;j<m;j++)
        {
            scanf("%d",&tmp);
            ptr[i][j]=-10*tmp;
        }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m-1;j++)
            printf("%d ",ptr[i][j]);
        printf("%d\n",ptr[i][m-1]);
    }

    for(int i=0;i<n;i++)
        free(ptr[i]);
    free(ptr);

    return 0;
}

int **Create2(int n,int m)
{
    int **ptr;
    ptr=malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
        ptr[i]=malloc(sizeof(int)*m);

    return ptr;
}
