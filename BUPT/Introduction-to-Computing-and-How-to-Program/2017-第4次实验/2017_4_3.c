#include<stdio.h>
//C.数列求和 2017-计算机导论与程序设计－第4次实验
//题目描述：有一分数序列：2/1, 3/2, 5/3, 8/5, 13/8, 21/13,……,先观察数列规律，再求出这个数列的前n项之和。
//考虑到提高结果精度，请用double型变量存储结果。
//输入格式：输入一个正整数n(1<=n<=50)，代表数列的项数。
//输出格式：输出序列的前n项和（保留的两位小数）。
int main(void)
{
    int n;
    double sum=0,a=2,b=1,tmp;

    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        sum+=a/b;
        tmp=a;
        a+=b;
        b=tmp;
    }
    printf("%.2lf",sum);
    
    return 0;
}
