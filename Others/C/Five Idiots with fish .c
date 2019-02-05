#include <stdio.h>

int main(void)
{
    int fsh,i,tmp=1;
    while(i!=5)
    {
        fsh=tmp+1;
        tmp=fsh;
        for(i=0;i<5;i++)
            if(fsh%4!=0)
                i=6;
            else
                fsh=fsh/4*5+1;
    }
        printf("%d",fsh);

        return 0;
}
