#include<stdio.h>
//把数反过来然后和原数比较
int main(void)
{
    int number,copy,a;
    printf("Please input a number:");
    scanf("%d",&number);
    copy=number;
    a=number%10;//number的末位
    number=number/10;//number的前几位
    while(number>=1)
    {
        a=a*10+number%10;//number的末位进位+number的前几位的末位
        number=number/10;//number的前几位
    }
    if(copy==a)
        printf("是回文数");
    else
        printf("不是回文数");
    return 0;
}
