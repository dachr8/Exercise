#include<stdio.h>
int main(void)
{
	char ch;
	int count=0;
	int num=0;
	scanf("%c",&ch);
	while(ch!='\n')
	{
		count++;
		num=num*10+ch-'0';
		scanf("%c",&ch);
	}
	//printf("\ncount:%d\n",count);
	int high,low;
	int copy=num;
	while(count>1)
	{
		int copy2=copy;
		for(int i=1;i<count;i++)
		{
			high=copy2/10;
			copy2=copy2/10;
		}
		low=copy-(copy/10)*10;
		//printf("\nhigh:%d\nlow:%d\n",high,low);
		if(high!=low)
		{
			printf("不是回文数");
			return 1;
		}
	for(int i=1;i<count;i++)
	high*=10;
	copy=(copy-high)/10;
	printf("\ncopy:%d\n",copy);
	count=count-2;
	}
	printf("回文数");
	return 0;
}

