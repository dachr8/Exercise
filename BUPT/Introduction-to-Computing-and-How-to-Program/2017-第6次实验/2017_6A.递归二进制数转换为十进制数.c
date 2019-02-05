#include <stdio.h>
//2017-计算机导论与程序设计-第6次实验
//A. 递归，二进制数转换为十进制数
//输入格式：输入一个整数n，代表二进制数，其长度不大于10
//输出格式：输入转换后的十进制数，占一行
int convert(int n);
int main(void)
{
    int n;

    scanf("%d",&n);
    printf("%d",convert(n));

    return 0;
}

int convert(int n)
{
    if(n==0||n==1)
        return n;
    else
        return n%10+convert(n/10)*2;
}