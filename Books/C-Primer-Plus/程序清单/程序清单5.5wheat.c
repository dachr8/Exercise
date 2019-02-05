#include <stdio.h>
#define SQUARES 64//棋盘中的方格数
//wheat.c--指数增长
int main(void)
{
    const double CROP=2e16;//世界小麦年产谷粒量
    double current,total;
    int count=1;

    printf("square\tgrains\t\ttotal\t\tfraction of\n");
    printf("      \tadded\t\tgrains\t\tworld total\n");
    total=current=1;//从1粒谷粒开始
    printf("%d    \t%.2e\t%.2e\t%.2e\n",count,current,total,total/CROP);
    printf("%d    \t%.2e\t%.2e\t%.2e\n",count,current,total,total/CROP);
    while(count<SQUARES)
    {
        count++;
        current=2*current;//下一个方格谷粒翻倍
        total+=current;//更新总数
        printf("%d    \t%.2e\t%.2e\t%.2e\n",count,current,total,total/CROP);
    }
    printf("That's all.\n");

    return 0;
}
