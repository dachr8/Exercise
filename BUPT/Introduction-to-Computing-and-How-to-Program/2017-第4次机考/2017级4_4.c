#include <stdio.h>

int main(void)
{
    int a,b,n,x,y;

    scanf("%d%d%d",&a,&b,&n);

    int source[b-a+1];

    source[0]=1;
    for(int i=1;i<b-a;i++)
        source[i]=2;
    source[b-a]=1;

    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        x=x<a?a:x;
        y=y>b?b:y;
        if(y>a&&x<b)
        {
            source[x-a]--;
            for(int j=x-a+1;j<y-a;j++)
                source[j]-=2;
            source[y-a]--;
        }

    }

    for(int i=0;i<=b-a;i++)
        if(source[i])
        {
            printf("-1");
            return 0;
        }

    printf("1");
    return 0;
}