#include <stdio.h>
#include <string.h>
//2017-计算机导论与程序设计-第10次实验
//C. 结构体排序
struct student
{
    char name[21];
    int score;
};

int main(void)
{
    int n;
    scanf("%d",&n);
    struct student a[n],tmp;

    for(int i=0;i<n;i++)
    {
        char t[0];
        scanf("%[\n]",t);
        scanf("%[^0-9] %d", a[i].name, &a[i].score);
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<n-1;j++)
            if(a[j].score<a[j+1].score||a[j].score==a[j+1].score&&strcmp(a[j].name,a[j+1].name)>0)
            {
                tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }

    for(int i=0;i<n;i++)
        printf("%s\n%d\n\n",a[i].name,a[i].score);

    return 0;
}
