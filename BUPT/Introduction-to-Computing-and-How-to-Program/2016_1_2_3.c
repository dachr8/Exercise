#include <stdio.h>

int main(void)
{
    char input,tmp;
    int a=0,b=0,c=0,max;//a=>0,b=>1,c=>-1
    scanf("%c",&input);
    while(input!='#')
    {
        switch(input)
        {
            case('0'):a++;break;
            case('1'):
                if(tmp=='-')
                    c++;
                else
                    b++;
                break;
            default:break;
        }
        tmp=input;
        scanf("%c",&input);
    }
    max=a>b?a:b;
    max=max>c?max:c;
    printf("%d %d %d\n%d",a,b,c,max);
    return 0;
}
