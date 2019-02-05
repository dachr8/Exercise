#include<stdio.h>
#include<math.h>
//2017-计算机导论与程序设计-第5次实验
//D. 设计函数isPrime与printFactor
int isPrime(int n);
void printFactor(int n);

int main(void)
{
    int a,b;

    scanf("%d%d",&a,&b);
    for(;a<=b;a++)
    {
        printf("%d=",a);
        if((isPrime(a)))
            printf("%d",a);
        else
            printFactor(a);
        printf("\n");
    }

    return 0;
}

int isPrime(int n)
{
    int sn=sqrt(n)+1;
    for(int i=2;i<=sn;i++)
        if(n%i==0)
            return 0;
    return 1;
}

void printFactor(int n)
{
    for(int i=2;n!=1;i++)
        {
            if(n%i==0)
            {
                printf("%d",i);
                n/=i;
                i--;
                if(n!=1)
                    printf("*");
            }
        }
}
