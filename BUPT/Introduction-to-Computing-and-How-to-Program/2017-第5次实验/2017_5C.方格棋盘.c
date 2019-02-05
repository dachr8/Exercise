#include<stdio.h>
//2017-计算机导论与程序设计-第5次实验
//C. 方格棋盘
int square(int a,int b);
int rectangle(int a,int b);

int main(void)
{
    int m,n;

    scanf("%d%d",&m,&n);
    printf("%d %d",square(m,n),rectangle(m,n));

    return 0;
}

int square(int a,int b)
{
    int n=0,c=a>b?b:a;
    for(int i=1;i<=c;i++)
        n+=(a-i+1)*(b-i+1);

    return n;
}

int rectangle(int a,int b)
{
    int n=0;

    for(int i=1;i<=a;i++)
        for(int j=1;j<=b;j++)
            if(i!=j)
                n+=(a-i+1)*(b-j+1);

    return n;
}
