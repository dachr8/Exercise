#include <stdio.h>
#include <string.h>
//2017-计算机导论与程序设计-第9次实验
//E. 字符串排序

int main(void)
{
    int n;

    scanf("%d",&n);

    char str[n][100],tmp;

    getchar();
    for(int i=0;i<n;i++)
        gets(str[i]);
    for(int i=0;i<n;i++)
        for(int j=0;j<n-1;j++)
            if(strcmp(str[j],str[j+1])>0)
                for(int k=0;str[j][k]||str[j+1][k];k++)
                {
                    tmp=str[j][k];
                    str[j][k]=str[j+1][k];
                    str[j+1][k]=tmp;
                }
    for(int i=0;i<n;i++)
        printf("%s\n",str[i]);

    return 0;
}
