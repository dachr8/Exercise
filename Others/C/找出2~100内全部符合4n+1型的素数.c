#include<stdio.h>
#include<math.h>
//找出2~100内全部符合4n+1型的素数
int isPrim(int num);
int main(void)
{
    for(int n=1;n<25;n++)
        if ((isPrim(4*n+1)))
            printf("%d=4*%d+1\n",4*n+1,n);

    return 0;
}

int isPrim(int num)//素数返回1，否则返回0
{
    int snum=sqrt(num);
    for(int i=2;i<=snum;i++)
    {
        if(num%i==0)
            return 0;
    }
    return 1;
}
