#include<stdio.h>

int main(void)
{
    int n=0,i,ii,j,k,l,m;

    for(i=4;i<100;i++)
    {
        ii=i*i;
        j=ii/1000;
        k=ii%1000/100;
        l=ii%100/10;
        m=ii%10;
        if(j==k&&l!=j&&m!=j&&l!=m)
        {
            if(j==0)
                printf("00");
            printf("%d\n",ii);
            n++;
        }
    }
    printf("%d",n);

    return 0;
}
