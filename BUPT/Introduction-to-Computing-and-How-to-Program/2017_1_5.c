#include<stdio.h>
//第一行：输入一行字符，以换行符‘\n’结束。(注：每个字符循环读取，不能用数组)。第二行：输出一个用户的id，换行。
int main(void)
{
    char ch_1,ch_2,ch_3,ch_4,id=' ';
    while(!('0'<=id&&id<='9'))
    {
        scanf("%c",&ch_1);
        scanf("%c",&ch_2);
        scanf("%c",&ch_3);
        scanf("%c",&ch_4);
        while(!(ch_1=='u'&&ch_2=='i'&&ch_3=='d'&&ch_4=='='))
        {
            ch_1=ch_2;
            ch_2=ch_3;
            ch_3=ch_4;
            scanf("%c",&ch_4);
        }
        scanf("%c",&id);
        if('0'<=id&&id<='9')
        {
            while('0'<=id&&id<='9')
            {
                printf("%c",id);
                scanf("%c",&id);
            }
        }
    }
    printf("\n");
    return 0;
}
