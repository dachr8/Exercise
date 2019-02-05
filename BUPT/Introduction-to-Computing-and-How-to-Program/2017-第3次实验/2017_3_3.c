#include <stdio.h>
#include <math.h>
//输入格式：输入四个正整数a、b、c、d，代表方程的系数。
//输出格式：输出方程在1附近的一个实根，占一行。
int main(void)
{
    double a,b,c,d,x=1,tmp=0,y,yy;
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
    while(fabs(x-tmp)>1e-5)
    {
        tmp=x;
        y=a*x*x*x+b*x*x+c*x+d;
        yy=3*a*x*x+2*b*x+c;
        x-=y/yy;
    }
    printf("%lf",x);

    return 0;
}
