#include <stdio.h>
//2017-计算机导论与程序设计-第10次实验
//B. 结构数组
struct student
{
    char name[21];
    char id[21];
    int score[5];
    double average;
    int total;
};

int main(void)
{
    int n;
    scanf("%d",&n);
    struct student a[n];

    for(int i=0;i<n;i++)
    {
        a[i].total=0;
        getchar();
        gets(a[i].name);
        gets(a[i].id);
        for(int j=0;j<5;j++)
        {
            scanf("%d",&a[i].score[j]);
            a[i].total+=a[i].score[j];
        }
        a[i].average=(double)a[i].total/5;
    }

    for(int i=0;i<n;i++)
    {
        printf("\nName:%s\n",a[i].name);
        printf("ID:%s\n",a[i].id);
        printf("Score:");
        for(int j=0;j<5;j++)
            printf("%d%c",a[i].score[j],j-4?' ':'\n');
        printf("average:%.2lf total:%d\n",a[i].average,a[i].total);
    }

    return 0;
}
