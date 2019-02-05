#include<stdio.h>
//第一行：三个整数(包括正整数、负整数或0)。第二行：输出判定结果：YES或NO，换行。
int main(void)
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if(a>0&&b>0&&c>0)
        if((a*a==b*b+c*c)||(b*b==a*a+c*c)||(c*c==a*a+b*b))
        printf("YES\n");
        else
        printf("NO\n");
    else
        printf("NO\n");
    return 0;
}
