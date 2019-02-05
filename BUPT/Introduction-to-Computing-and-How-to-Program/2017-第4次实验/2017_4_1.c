#include<stdio.h>
//A.实心菱形 2017-计算机导论与程序设计－第4次实验
//题目描述：已知一个整数n（n为正整数），你要根据n打印出n阶的实心菱形
//输入格式：输入一个整数n(要打印的菱形阶数)
//输出格式：输出n阶实心菱形(占2*n-1行)
//补充说明：每行的*符号后不需要跟空格

int main(void)
{
    int n;

    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        for(int j=n;j>i+1;j--)
            printf(" ");
        for(int j=0;j<2*i+1;j++)
            printf("*");
        printf("\n");
    }
    for(int i=n-1;i>0;i--)
    {
        for(int j=n;j>i;j--)
            printf(" ");
        for(int j=0;j<2*i-1;j++)
            printf("*");
        printf("\n");
    }

    return 0;
}
