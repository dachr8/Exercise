#include <stdio.h>
//post_pre.c--前缀和后缀
int main(void)
{
    int a=1,b=1;
    int a_post,pre_b;

    a_post=a++;//后缀递增
    pre_b=++b;//后缀递增
    printf("a\ta_post\tb\tpre_b\n");
    printf("%d\t%d\t\t%d\t%d\n",a,a_post,b,pre_b);

    return 0;
}
