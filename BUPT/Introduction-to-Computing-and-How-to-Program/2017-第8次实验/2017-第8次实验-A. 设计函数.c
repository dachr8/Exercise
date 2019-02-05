#include <stdio.h>
//2017-计算机导论与程序设计-第8次实验
//A. 设计函数
void insertSort(int a[],int n);

int main(void)
{
    int n;

    scanf("%d",&n);

    int a[n];

    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    insertSort(a,n);
    for(int i=0;i<n-1;i++)
        printf("%d ",a[i]);
    printf("%d\n",a[n-1]);

    return 0;
}

void insertSort(int a[],int n)
{
    int tmp,j;
    for(int i=0;i<n;i++)
    {
        if(i<n-1)
            j=i;
        while(a[j]>a[j+1])
        {
            tmp=a[j];
            a[j]=a[j+1];
            a[j+1]=tmp;
            j--;
        }
    }
}
