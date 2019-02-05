#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    for(int i=1;i<=20;i++)
    {
        printf("\t%d",1+rand()%6);
        if(i%5==0)
            printf("\n");
    }

    return 0;
}
