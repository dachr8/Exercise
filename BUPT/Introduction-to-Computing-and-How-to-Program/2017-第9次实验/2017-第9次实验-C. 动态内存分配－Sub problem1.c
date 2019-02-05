#include <stdio.h>
#include <stdlib.h>
//2017-计算机导论与程序设计-第9次实验
//C. 动态内存分配－Sub problem1

int *Create1(int n);

int main(void)
{
    int n;
    int *ptr;

    scanf("%d",&n);

    ptr=Create1(n);

    for(int i=0,tmp;i<n;i++)
    {
        scanf("%d",&tmp);
        *(ptr+i)=-10*tmp;
    }

    for(int i=0;i<n;i++)
        printf("%d ",*(ptr+i));

    free(ptr);

    return 0;
}

int *Create1(int n)
{
    return malloc(sizeof(int)*n);
}
