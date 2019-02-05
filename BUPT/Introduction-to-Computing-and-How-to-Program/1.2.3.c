#include <stdio.h>
//第1题. 实验手册中实验2的第3题（幂计算）
int main(void)
{
    int x,y;
    int z=1;
    printf("Please input two integers:");
    scanf("%d%d",&x,&y);
    for(int i=1;i<=y;i++)
    {
        z*=x;
    }
    printf("The result of %d to power %d is %d.",x,y,z);
    return 0;
}
