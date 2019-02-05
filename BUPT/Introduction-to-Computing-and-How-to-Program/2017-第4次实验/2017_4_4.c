#include<stdio.h>
#include<math.h>
//D.千分位格式 2017-计算机导论与程序设计－第4次实验
//题目描述：已知一个正整数n，你要将它输出成“千分位”形式。即从个位数起，每3位之间加一个逗号。
//例如，将“7654321”写成“7,654,321”。
//输入格式：输入一个正整数n。
//输出格式：输出这个整数的“千分位”输出形式，占一行。
int main(void)
{
    int n,tmp,num,p;

    scanf("%d",&n);
    tmp=n;
    for(num=1;tmp>9;num++)
    {
        tmp/=10;
    }
    for(tmp=num;tmp>0;tmp--)
    {
        if(tmp%3==0&&tmp!=num)
            printf(",");
        p=(pow(10,tmp-1));
        printf("%d",n/p);
        n-=n/p*p;
    }

    return 0;
}
