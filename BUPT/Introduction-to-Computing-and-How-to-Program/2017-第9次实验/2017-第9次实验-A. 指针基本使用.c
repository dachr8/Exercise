#include <stdio.h>
//2017-计算机导论与程序设计-第9次实验
//A. 指针基本使用

char *locatesubstr(char *str1,char *str2);

int main(void)
{
    char str1[500],str2[500];

    gets(str1);
    gets(str2);

    printf("%s",locatesubstr(str1,str2));

    return 0;
}

char *locatesubstr(char *str1,char *str2)
{
    if(*str2)
        while (*str1)
        {
            for(int i=0;*(str1+i)==*(str2+i);i++)
                if(!*(str2+i+1))
                    return str1;
            str1++;
        }
    else
        return str1;
    return "NULL";
}
