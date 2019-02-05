#include <stdio.h>
//2017-计算机导论与程序设计-第8次实验
//B. 设计递归函数
int recurBinarySearch(int a[],int begin,int end,int key);

int main(void)
{
    int n,key;

    scanf("%d",&n);

    int a[n];

    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&key);

    printf("%d\n",recurBinarySearch(a,0,n,key));

    return 0;
}

int recurBinarySearch(int a[],int begin,int end,int key)
{
    int bin=(begin+end)/2;
    if(a[bin]>key)
        return recurBinarySearch(a,begin,bin,key);
    if(a[bin]<key)
        return recurBinarySearch(a,bin,end,key);
    if(a[bin]==key)
        return bin;
    if(begin==end)
        return -1;
}
