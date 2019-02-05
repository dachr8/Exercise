#include <stdio.h>
//1132. 判断字符相邻
int main(void)
{
    char a,b,c,tempo;
    scanf("%c%c%c",&a,&b,&c);
    if(('a'<b&&b<'z'||'A'<b&&b<'Z')&&(a==b-1)&&(c==b+1))
        printf("The letters are adjacent with each other.");
    else
        printf("The letters are not adjacemnt with each other.");
    return 0;
}
