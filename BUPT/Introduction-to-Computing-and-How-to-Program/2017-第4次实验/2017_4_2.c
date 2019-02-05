#include<stdio.h>
//B.抽签结果 2017-计算机导论与程序设计－第4次实验
//题目描述：两个乒乓球队进行对抗赛，甲队出A、B、C、D四人；乙队出W、X、Y、Z四人
//已知部分抽签结果是：A不与X比赛，C不与X、Z比赛，D不与W比赛
//你的任务是将全部可能的抽签结果打印出来
//There are 7 ways to assign the players.
int main(void)
{
    char vsA,vsB,vsC,vsD;
    int group=1;

    printf("There are 7 ways to assign the players.\n");
    for(vsA='W';vsA<='Z';vsA++)
    {
        if(vsA=='X')
            vsA++;
        for(vsB='W';vsB<='Z';vsB++)
        {
            if(vsB==vsA)
                vsB++;
            for(vsC='W';vsC<='Z'&&vsB<='Z';vsC++)
            {
                if(vsC=='X'||vsC=='Z'||vsC==vsA||vsC==vsB)
                    vsC++;
                if(vsC=='X'||vsC=='Z'||vsC==vsA||vsC==vsB)
                    vsC++;
                if(vsC=='X'||vsC=='Z'||vsC==vsA||vsC==vsB)
                    vsC++;
                for(vsD='X';vsD<='Z'&&vsC<'Z'&&vsB<='Z';vsD++)
                {
                    if(vsD!=vsA&&vsD!=vsB&&vsD!=vsC)
                        {
                        printf("Group %d:\n",group);
                        printf("A VS %c\n",vsA);
                        printf("B VS %c\n",vsB);
                        printf("C VS %c\n",vsC);
                        printf("D VS %c\n",vsD);
                        group++;
                    }
                }
            }
        }
    }

    return 0;
}
