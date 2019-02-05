#include<stdio.h>
     int main(void)
{
	double a;
	printf("输入杯数:");
	scanf("%lf",&a);
	printf("品脱:%f\n",a/2);
	printf("盎司:%f\n",a*8);
	printf("汤勺:%f\n",a*8*2);
	printf("茶勺:%f\n",a*8*2*3);
	return 0;
}
