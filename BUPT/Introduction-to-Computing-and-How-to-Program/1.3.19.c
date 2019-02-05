#include <stdio.h>
#include <math.h>
//第4题. 实验手册中实验3的第19题（复杂选择结构练习）
int main(void)
{
    float a,b,c,delta;
    printf("Please input three float numbers:");
    scanf("%f%f%f",&a,&b,&c);
    delta=b*b-4*a*c;
    if(a==0)
        printf("The equation is not quadratic.");
    else if(delta==0)
        printf("The equation has two equal roots:%.4f.",-b/(2*a));
    else if(delta>0)
        printf("The equation has two distinct real roots:%.4f and %.4f.", (-b+sqrt(delta))/(2*a), (-b-sqrt(delta))/(2*a));
    else
        printf("The equation has two complex roots:%.4f+%.4fi and %.4f-%.4fi.",-b/(2*a),sqrt(-delta)/(2*a),-b/(2*a),sqrt(-delta)/(2*a));
    return 0;
}