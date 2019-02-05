#include <stdio.h>

int main(void)
{
    int a[20],n=0;

    scanf("%d",&a[0]);
    while(a[n++]+1)
        scanf("%d",&a[n]);
    n--;

    for(int i=0;i<n;i++)
        if(a[i]%2)
            for(int j=i,tmp;j>0&&(!(a[j-1]%2)||a[j-1]>a[j]);j--)
            {
                tmp=a[j-1];
                a[j-1]=a[j];
                a[j]=tmp;
            }

    for(int i=0;i<n;i++)
        printf("%d%c",a[i],i-n+1?' ':'\n');
}
