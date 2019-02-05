#include<stdio.h>
//flag=0，初始
//flag=1,递增
//flag=2,递减
int main(void)
{
    int len=1,max_len=1,flag=0;
    char ch,pre_ch;

    scanf("%c",&pre_ch);
    scanf("%c",&ch);
    while(ch!='\n')
    {
        if(ch==pre_ch+1&&flag!=2)//递增，之前不递减
        {
            len++;
            flag=1;
        }
        else if(ch==pre_ch+1&&flag==2)//递增，之前递减
        {
            len=2;
            flag=1;
        }
        else if(ch==pre_ch-1&&flag!=1)//递减，之前不递增
        {
            len++;
            flag=2;
        }
        else if(ch==pre_ch-1&&flag==1)//递减，之前递增
        {
            len=2;
            flag=2;
        }
        else//既不递增也不递减
        {
            len=1;
            flag=0;
        }
        max_len=max_len>len?max_len:len;
        pre_ch=ch;
        scanf("%c",&ch);
    }
    printf("%d",max_len);

    return 0;
}
