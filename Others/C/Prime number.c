#include <stdio.h>
#include <math.h>

int prim(int num);

int main(void)
{
    int n;

    scanf("%d",&n);
    printf("%d=",n);
    prim(n);

    return 0;
}

int prim(int num)
{
    int snum=sqrt(num);
    for(int i=2;i<=snum;i++)
    {
        if(num%i==0)
        {
            printf("%d*",i);
            return prim(num/i);
        }
    }
    printf("%d",num);
    return 1;
}
