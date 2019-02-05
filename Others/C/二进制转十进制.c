#include<stdio.h>
int main(void) 
{
	char ch;
	int num;
	scanf("%c",&ch);
	while(ch!='\n')
	{
		num=num*2+ch-'0';
		scanf("%c",&ch);
	} 
	printf("%d",num);
	 return 0;
}
