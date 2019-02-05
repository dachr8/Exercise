#include <stdio.h>
//第1题. 实验手册中实验1的第1题 (求两数的和与差)
int main(void)
{
    int number1,number2;
    printf("Please input two integers:");
    scanf("%d%d",&number1,&number2);
    printf("The sum is %d and the difference is %d",number1+number2,number1-number2);
    return 0;
}
