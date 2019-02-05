#include <stdio.h>
#include <math.h>
//输入格式：输入一个浮点数x，即代表ex中的指数x,且x满足x<=20。输出格式：输出ex的值，保留4位有效数字，占一行。
int main(void)
{
    double x,xn,ex=1,n=1,i=1;
    scanf("%lf",&x);
    //printf("%.4lf\n",exp(x));
    xn=x;
    ex+=xn/n;
    while(fabs(xn/n)>=1e-8)
    {
        xn*=x;
        n*=(i+1);
        i++;
        ex+=xn/n;
    }
    printf("%.4lf\n",ex);
    return 0;
}
