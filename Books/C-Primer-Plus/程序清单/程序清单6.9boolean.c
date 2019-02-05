#include <stdio.h>
//boolean.c--Use a variable of type _Bool
int main(void)
{
    long num,sum=0L;//把sum初始化为0
    _Bool inputisGood=(scanf("%ld",&num)==1);

    printf("Please enter an integer to be summed (q to quit): ");
    while(inputisGood)
    {
        sum+=num;
        printf("Please enter next integer (q to quit): ");
        inputisGood=(scanf("%ld",&num)==1);
    }
    printf("Those integers sum to %ld.\n",sum);

    return 0;
}
