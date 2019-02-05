#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CreatArray(int [],int);
void OutArray(int [],int);
int SearchArray(int [],int,int x);
int main(void)
{
    int size=20,a[size],x,i=0;
    CreatArray(a,size);
    OutArray(a,size);
    printf("\n");
    scanf("%d",&x);
    printf("%d",SearchArray(a,size,x));
    return 0;
}

void CreatArray(int array[],int size)
{
    srand(time(NULL));
    for(int i=0;i<size;i++)
        array[i]=rand()%100;
}

void OutArray(int array[],int size)
{
    for(int i=0;i<size;i++)
        printf("%d\t",array[i]);
}

int SearchArray(int array[],int size,int x)
{
    for(int i=0;i<size;i++)
        if(array[i]==x)
            return i;
    return -1;
}
