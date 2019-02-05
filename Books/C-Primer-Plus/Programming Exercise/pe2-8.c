#include<stdio.h>
     void one_three(void),two(void);
     int main(void)
{
	printf("starting now:\n");
	one_three();
	printf("done!");
}
     void one_three(void)
{
	printf("one\n");
	two();
	printf("three\n");
}
     void two(void)
{
	printf("two\n");
}
