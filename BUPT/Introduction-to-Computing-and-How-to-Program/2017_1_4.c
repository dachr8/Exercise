#include<stdio.h>
//第一行：输入多个非零整数，以0标识结束。(注：每个整数循环读取，不要用数组)。第二行：最小正整数，最后换行。
int main(void)
{
    int input,min;
    scanf("%d",&min);
    while(min<0)
        scanf("%d",&min);
    scanf("%d",&input);
    while(input!=0)
    {
        if(input>0)
            min=min<input?min:input;
        scanf("%d",&input);
    }
    printf("%d\n",min);
    return 0;
}
