#include <stdio.h>
//2017级机考4_1
//1.给定一个一维整数数组，要求对其进行排序，并从小到达对其输出。
//2.假设用户输入肯定正确，程序不需要对异常输入进行处理。请写出完整C语言程序。
//输入与输出说明：
//第一行: 一个正整数n(0<n<1000), 表示数组的长度, 以换行符’\n’结束。
//第二行: n个待排序的整数，空格分隔, 以换行符’\n’结束。
//第三行: 从小到大对其进行输出，空格分隔，以换行符’\n’结束。

int main(void)
{
    int n;

    scanf("%d",&n);

    int a[n];

    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    for(int i=0;i<n;i++)
        for(int j=0,tmp;j<n-1;j++)
            if(a[j]>a[j+1])
            {
                tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }

    for(int i=0;i<n-1;i++)
        printf("%d ",a[i]);
    printf("%d\n",a[n-1]);

    return 0;
}
