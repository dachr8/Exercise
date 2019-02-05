#include <stdio.h>

int factorial(int n);

int main(void)
{
    int n;

    scanf("%d",&n);
    printf("%d!=",n);
    printf("=%d",factorial(n));

    return 0;
}

int factorial(int n)
{
    if(n==1)
    {
        printf("1");
        return 1;
    }
    else
    {
        printf("%d*",n);
        return n*factorial(n-1);
    }
}
