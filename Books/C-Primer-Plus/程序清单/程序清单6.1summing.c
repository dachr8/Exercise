#include <stdio.h>
//summing.c--Summation of integers based on user type
int main(void)
{
    long num,sum=0L;//把sum初始化为0

    printf("Please enter an integer to be summed (q to quit): ");
    while(scanf("%ld",&num)==1)
    {
        sum+=num;
        printf("Please enter next integer (q to quit): ");
    }
    printf("Those integers sum to %ld.\n",sum);

    return 0;
}
