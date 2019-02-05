#include<stdio.h>
     int main(void)
{
	double a;
	printf("输入身高（/英寸）:");
	scanf("%lf",&a);
	printf("身高（/厘米）:%lf",a*2.54/7.1);
	return 0;
}
