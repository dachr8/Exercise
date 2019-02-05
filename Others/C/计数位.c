#include<stdio.h>
int main(void) 
{
	char ch;
	int num=0;
	scanf("%c",&ch);
	while(ch!='\n')
	{
		num++;
		scanf("%c",&ch);
	} 
	printf("%d",num);
	 return 0;
}
