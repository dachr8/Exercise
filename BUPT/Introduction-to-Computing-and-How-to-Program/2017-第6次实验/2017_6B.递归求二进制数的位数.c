#include <stdio.h>
#include <math.h>
//2017-计算机导论与程序设计-第6次实验
//B. 递归，求二进制数的位数
//输入格式：输入一个非负整数n
//输出格式：输出n的二进制位数，占一行
int countBinary(int n);
int main(void)
{
    int n;

    scanf("%d",&n);
    printf("%d",countBinary(n));

    return 0;
}

int countBinary(int n)
{
    return n>1?countBinary(n>>1)+1:1;
}
