#include <stdio.h>
//2017-计算机导论与程序设计-第8次实验
//D. 字符串处理
void delcharfun(char str[],char ch);

int main(void)
{
    char str[100],ch;

    scanf("%s",str);
    getchar();
    ch=getchar();
    delcharfun(str,ch);
    printf("%s",str);

    return 0;
}

void delcharfun(char str[],char ch)
{
    int found=1;
    while(found)
    {
        found=0;
        for(int i=found;i<100;i++)
            if(str[i]==ch)
            {
                for(int j=i;j<100;j++)
                    str[j]=str[j+1];
                found=i;
            }

    }
}
