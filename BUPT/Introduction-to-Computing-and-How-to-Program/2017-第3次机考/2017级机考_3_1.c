#include <stdio.h>

//2017-计算机导论与程序设计-第3次机考
//A. 2017级机考_3_1
//1.假设某本书共有n页，页码从1到n，n是不确定且需要输入的。请设计算法，统计这本书页码中0~9每个数字分别出现了多少次 。
//2.假设用户输入肯定正确，程序不需要对异常输入进行处理。请写出完整C语言程序。
//3.本题可以使用数组存放统计结果。
//输入与输出说明：
//第一行：输入一个整数n (1 ≤ n ≤ 1,000,000)。
//第二行：输出10个整数，每个整数对应0~9这十个数字在页码中出现的次数。整数间以一个空格分隔，行末无空格，换行结束。

int num(int n,int x);

int main(void)
{
    int n;

    scanf("%d",&n);
    for(int i=0;i<=9;i++)
        printf("%d%c",num(n,i),i-9?' ':'\n');

    return 0;
}

int num(int n,int x)
{
    int sum=0,nCopy=n;

    while(nCopy>0)
    {
        sum+=(nCopy%10==x);
        nCopy/=10;
    }

    return sum+(n-1?num(n-1,x):0);
}
