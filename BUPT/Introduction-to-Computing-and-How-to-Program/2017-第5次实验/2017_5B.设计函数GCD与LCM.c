#include<stdio.h>
//2017-计算机导论与程序设计-第5次实验
//B. 设计函数GCD与LCM
int GCD(int a,int b);
int LCM(int a,int b);

int main(void)
{
    int m,n;

    scanf("%d%d",&m,&n);
    printf("%d %d",GCD(m,n),LCM(m,n));

    return 0;
}

int GCD(int a,int b)
{
    while(a!=b)
    {
        if(a>b)
            a-=b;
        else
            b-=a;
    }

    return a;
}

int LCM(int a,int b)
{
    return a*b/GCD(a,b);
}
