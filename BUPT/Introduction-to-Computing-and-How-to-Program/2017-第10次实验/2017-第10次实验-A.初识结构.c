#include <stdio.h>
//2017-计算机导论与程序设计-第10次实验
//A. 初识结构
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
    struct student a={{0},{0},{0},0,0,};

    gets(a.name);
    gets(a.id);
    for(int i=0;i<5;i++)
    {
        scanf("%d",&a.score[i]);
        a.total+=a.score[i];
    }
    a.average=(double)a.total/5;

    for(int i=0,tmp;i<5;i++)
        for(int j=0;j<4;j++)
            if(a.score[j]<a.score[j+1])
            {
                tmp=a.score[j];
                a.score[j]=a.score[j+1];
                a.score[j+1]=tmp;
            }


    printf("%s\n",a.name);
    printf("%s\n",a.id);
    for(int i=0;i<5;i++)
        printf("%d%c",a.score[i],i-4?' ':'\n');
    printf("%.2lf %d",a.average,a.total);

    return 0;
}
