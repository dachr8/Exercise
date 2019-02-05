#include <stdio.h>
#include <math.h>
//2017-计算机导论与程序设计-第6次实验
//C. 完全平方回文数
//输入格式：输入一个非负整数n，代表待验证的数
//输出格式：输出判断结果，占一行
int isPalindrome(int n);
int main(void)
{
    int n;

    scanf("%d",&n);
    if((isPalindrome(n))&&sqrt(n)==(int)sqrt(n))
        printf("Yes");
    else
        printf("No");

    return 0;
}
int isPalindrome(int n)
{
    int copy,a;
    copy=n;
    a=n%10;//n的末位
    n=n/10;//n的前几位
    while(n>=1)
    {
        a=a*10+n%10;//n的末位进位+n的前几位的末位
        n=n/10;//n的前几位
    }
    if(copy==a)
        return 1;
    else
        return 0;
}
