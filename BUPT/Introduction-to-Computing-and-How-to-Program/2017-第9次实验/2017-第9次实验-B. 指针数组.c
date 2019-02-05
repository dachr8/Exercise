#include <stdio.h>
#include <string.h>
//2017-计算机导论与程序设计-第9次实验
//B. 指针数组

int main(void)
{
    char str[10001],*word[1001];
    int j=0,len;

    gets(str);
    len=strlen(str);

    word[0]=&str[0];
    for(int i=0;i<len;i++)
        if(str[i]==' ')
        {
            str[i]='\0';
            j++;
            word[j]=&str[i+1];
        }

    for(int i=0;i<=j;i++)
        printf("%s\n",word[i]);

    return 0;
}
