#include<stdio.h>
#include<math.h>
//判断四位素数的逆数是否是素数
int reverse(int num);
int isPrim(int num);
int main(void)
{
    for(int num=1000;num<10000;num++)
    {
        if (isPrim(num)==1)
        {
            if(isPrim(reverse(num))==1)
                printf("%d\n",num);
        }
    }

    return 0;
}

int isPrim(int num)
{
    int snum=sqrt(num);
    for(int i=2;i<=snum;i++)
    {
        if(num%i==0)
            return 0;
    }

    return 1;
}

int reverse(int num)
{
    int reverse=num%10;//num的末位
    num=num/10;//num的前几位
    while(num>=1)
    {
        reverse=reverse*10+num%10;//num的末位进位+num的前几位的末位
        num=num/10;//num的前几位
    }

    return reverse;

}
