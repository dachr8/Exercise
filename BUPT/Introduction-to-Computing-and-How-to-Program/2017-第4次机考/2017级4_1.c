#include <stdio.h>

int main(void)
{    int n;

    scanf("%d",&n);

    for(int i=0;6*i<=n;i++)
        if(!((n-i*6)%8))
        {
            printf("%d,%d",(n-i*6)/8,i);
            return 0;
        }

    printf("-1");
    return 0;
}
