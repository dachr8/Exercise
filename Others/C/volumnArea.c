#include <stdio.h>
void volumnArea(int length,int width,int height,int *volumnPtr,int *areaPtr);
int main(void)
{
    int a,b,c,v,s;
    scanf("%d%d%d",&a,&b,&c);
    volumnArea(a,b,c,&v,&s);
    printf("%d\n%d",v,s);
    return 0;
}

void volumnArea(int length,int width,int height,int *volumnPtr,int *areaPtr)
{
    *volumnPtr=length*width*height;
    *areaPtr=2*(length*width+length*height+width*height);
}
