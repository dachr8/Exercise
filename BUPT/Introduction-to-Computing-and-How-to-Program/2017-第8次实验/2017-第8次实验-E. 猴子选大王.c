#include <stdio.h>
//2017-计算机导论与程序设计-第8次实验
//E. 猴子选大王
int main(void)
{
    int m,n,a[101],i,num,count;

    //printf("Enter the total number of monkeys: ");
    scanf("%d",&n);
    //printf("Enter the number of intervals: ");
    scanf("%d",&m);
    for(i=1;i<=n;i++)
        a[i]=i;

    num=n;
    i=0;
    while(num>1)
    {
        count=0;
        while(count<m)
        {
            i++;
            if(i>n)
                i=1;
            if(a[i])
                count++;
        }
        a[i]=0;
        //printf("No.%d monkey out of the circle\n",i);
        num--;
    }
    for(i=1;i<=n;i++)
        if(a[i]==i)
            printf("%d",i);//printf("No.%d is the king",i);

    return 0;
}
