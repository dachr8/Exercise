#include<stdio.h>
//第一行：输入多个非负整数，由-1标识结束。第二行：输出低于80分的整数数量，换行
int main(void)
{
    int score,count=0;
    scanf("%d",&score);
    while(score!=-1)
    {
        if(score<80)
            count++;
        scanf("%d",&score);
    }
    printf("%d\n",count);
    return 0;
}
