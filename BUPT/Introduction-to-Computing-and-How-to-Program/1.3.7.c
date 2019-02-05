#include <stdio.h>
//第2题. 实验手册中实验3的第7题 (一批字符数据的处理,循环嵌套选择)
int main(void)
{
    int characters=0;
    int spaces=0;
    int numbers=0;
    int others=0;
    char ch=0;
    printf("Please input a string:");
    while((ch=getchar())!=EOF)
    {
        if(ch=='\n')
            break;
        if('a'<=ch&&ch<='z'||'A'<=ch&&ch<='Z')
            characters++;
        else if(ch==' ')
            spaces++;
        else if('0'<=ch&&ch<='9')
            numbers++;
        else
            others++;
    }
    printf("The number of English characters, spaces, numbers, other characters are:%d %d %d %d",characters,spaces,numbers,others);
    return 0;
}
