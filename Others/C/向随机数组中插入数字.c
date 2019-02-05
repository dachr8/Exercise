#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int a[10],n,p;
	
    srand(time(NULL));
    for(int i=0;i<9;i++)
    {
    	a[i]=1+rand()%9;
        printf("\t%d",a[i]);
    }
    printf("\n");
    scanf("%d%d",&n,&p);
    for(int i=9;i>=p;i--)
    	a[i+1]=a[i];
    a[p]=n;
    for(int i=0;i<9;i++)
        printf("\t%d",a[i]);
    
    return 0;
}
