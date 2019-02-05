#include<stdio.h>
     int main(void)
{
	int a;
	int b=3.156e7;
	printf("输入年龄:");
	scanf("%d",&a);
	printf("年龄对应的秒数:%u",b*a); 
//printf("年龄对应的秒数:%d",3.156e7*a);不可行,似乎带e的都不可用 ?
	return 0;
}
