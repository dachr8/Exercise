#include <stdio.h>
//将字符按大小排序
int main(void)
{
    char a,b,c,tempo;
    scanf("%c%c%c",&a,&b,&c);
    if(a>b)
    {
        tempo=a;
        a=b;
        b=tempo;
    }
    if(b>c)
    {
        tempo=b;
        b=c;
        c=tempo;
    }
    if(a>b)
    {
        tempo=a;
        a=b;
        b=tempo;
    }
    printf("%c%c%c",a,b,c);
    return 0;
}
