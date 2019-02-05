#include <stdio.h>
#define PAGES 959
//width.c--字段长度
int main(void)
{
    printf("*%d*\n",PAGES);
    printf("*%2d*\n",PAGES);
    printf("*%10d*\n",PAGES);
    printf("*%-10d*\n",PAGES);
    return 0;
}
