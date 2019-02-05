#include <stdio.h>

int scanfLine(int [],int);

int main(void)
{
    int a[99],b[99],aEnd=0,bEnd=0,i,j,tmp;

    aEnd=scanfLine(a,99);
    bEnd=scanfLine(b,99);
    for(i=0;i<bEnd;i++)
        a[aEnd++]=b[i];
    for(i=0;i<aEnd;i++)
    {
        for(j=i+1;j<aEnd;j++)
        {
            if(a[i]>a[j])
            {
                tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
            }
        }
    }
    i=0;
    while(i<aEnd)
        printf("%d\t",a[i++]);

    return 0;
}

int scanfLine(int a[],int End)
{
    int end=0;
    scanf("%d",&a[end++]);
    while(getchar()!='\n')
        scanf("%d",&a[end++]);

    return end;
}
