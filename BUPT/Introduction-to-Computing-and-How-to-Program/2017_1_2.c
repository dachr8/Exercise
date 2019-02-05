#include<stdio.h>
//第一行：由‘W’和‘L’两个字符组成的字符串，以换行符‘\n’结束。第二行：输出游戏胜率，小数点后保留两位有效数字，换行。
int main(void)
{
    char result;
    float win=0,sum=0;
    scanf("%c",&result);
    while(result!='\n')
    {
        sum++;
        if(result=='W')
            win++;
        scanf("%c",&result);
    }
    printf("%.2f\n",win/sum);
    return 0;
}
