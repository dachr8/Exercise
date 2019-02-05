#include <stdio.h>
#define SIZE 10
void bubbleSort(int *,int);

int main(void)
{
    int i,a[SIZE]={2,6,4,8,10,12,89,68,45,37};

    printf("Data items in original order\n");
    for (i=0;i<SIZE;i++)
        printf("%4d",a[i]);
    bubbleSort(a, SIZE);
    printf("\nData items in ascending order\n");
    for (i=0;i<SIZE;i++)
        printf("%4d",a[i]);

    return 0;
}

void bubbleSort(int *array,const int size)
{
    void swap(int *,int *);//Function prototype

    for(int pass=1;pass<size;pass++)
        for(int i=0;i<size-pass;i++)
            if(array[i]>array[i+1])
                swap(&array[i],&array[i+1]);
}

void swap(int *num1Ptr,int *num2Ptr)//Function: Swap the variable pointed to by the pointer
{  int tmp=*num1Ptr;
    *num1Ptr=*num2Ptr;
    *num2Ptr=tmp;
}
