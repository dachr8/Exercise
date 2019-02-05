#include <stdio.h>
//2017-计算机导论与程序设计-第6次实验
//D. 无重复数字
//问题描述：已知正整数a、b、n满足a<=b。你的任务是求出区间[a,b]内所有满足以下条件的整数:
//        1.该整数由1到n这n个数字组成。2.整数中各个位上的数字不相同。
//输入格式：输入三个正整数a、b、n，其中a、b代表所求区间，满足1<=a<=b<=2000，且1<=n<=9
//输出格式：输出满足条件的整数，每五个数为一行，整数之间用tab分隔，最后一个数后为换行符；
//        当该区间没有符合条件的整数时，输出“There is no proper number in the interval.”
int main(void)
{
    int a,b,n,n1,n2,n3,n4,count=0;

    scanf("%d%d%d",&a,&b,&n);
    for(int i=a;i<=b;i++)
    {
        n1=i/1000;
        n2=i/100%10;
        n3=i/10%10;
        n4=i%10;
        if(n4==0)
            i++;
        else if(n3==0&&n2!=0)
            i+=10;
        else if(n2==0&&n1!=0)
            i+=100;
        else if(n4>n)
            i+=(9-n);
        else if(n3>n)
            i+=((9-n)*10-1);
        else if(n2>n)
            i+=((9-n)*100-1);
        else if(n1!=n2&&n1!=n3&&n1!=n4&&n2!=n3&&n2!=n4&&n3!=n4)
        {
            printf("%d",i);
            count++;
            if(count%5!=0)
                printf("\t");
            else
                printf("\n");
        }
    }
    if(count==0)
        printf("There is no proper number in the interval.");

    return 0;
}
