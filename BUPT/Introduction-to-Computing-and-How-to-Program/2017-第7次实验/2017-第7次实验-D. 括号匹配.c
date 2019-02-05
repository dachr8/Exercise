#include <stdio.h>
//2017-计算机导论与程序设计-第7次实验
//D. 括号匹配
int main(void)
{
    int ch,match=0;

    ch=getchar();
    while(ch!='#')
    {
        if(ch=='(')
            match++;
        if(ch==')')
            match--;
        if(match<0)
        {
            printf("\nNO");
            return 0;
        }
        ch=getchar();
    }

    if(match)
        printf("\nNO");
    else
        printf("\nYES");

    return 0;
}
