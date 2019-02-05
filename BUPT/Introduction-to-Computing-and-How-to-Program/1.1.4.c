#include <stdio.h>
//第3题. 实验手册中实验1的第4题（求圆的周长与面积）
#define PI 3.14159265
int main(void)
{
    double R;
    printf("Please input a float number:");
    scanf("%lf",&R);
    printf("The perimeter is %.4lf,the area is %.4lf.",2*PI*R,PI*R*R);
    return 0;
}
