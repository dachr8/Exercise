#include <stdio.h>
//输入格式：第一行输入一个非负整数n
//        第二行输入数组
//输出格式：输出数组
int main(void)
{
    int a[101],n,i=0,j=0,end=0;

    scanf("%d",&n);
    scanf("%d",&a[i]);
    while(a[i++]!=-1)
        scanf("%d",&a[i]);//为有效数组长度i，a[i-1]为末位
    while(j+n<i)
    {
        end=j+n-1;
        while(end!=j-1)
            printf("%d ",a[end--]);
        j+=n;
    }
    while(j<i-1)
        printf("%d ",a[j++]);

    return 0;
}
