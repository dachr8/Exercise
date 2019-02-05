#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

typedef struct card
{
    char * month,* type;
}Card;

enum months {song,mei,ying,teng,changpu,mudan,qiu,mang,ju,hongye,liu,tong};

int startKoikoi(Card * deck);
void shuffle(Card * deck);
void showOneTable(Card * table,int max,int state);
void showOneCard(Card * deck,int n);
void playOneCard(Card * hand,Card * table,Card * playertable,int num,int level);
int checkHandCombo(Card * hand);
int checkTableCombo(Card * table,int ifHandCombo);
char ifKoikoi(int turn);

int main(void)
{
    enum months month;
    int point[2]={0,0},tmp;
    Card deck[48];
    char * monthName[]={"松","梅","樱","藤","菖蒲","牡丹","萩","芒","菊","红叶","柳","桐"};
    char restart='Y',ch;

    srand(time(NULL));

    for(month=song;month<=tong;month++)
    {
        for(int i=0;i<4;i++)
            deck[month*4+i].month=monthName[month];

        if(month==mang||month==tong)
            deck[month*4].type="素";
        else
            deck[month*4].type="短";

        if(month==song||month==ying||month==tong)
            deck[month*4+1].type="素";
        else
            deck[month*4+1].type="种";

        if(month==song||month==ying||month==mang||month==liu||month==tong)
            deck[month*4+2].type="光";
        else
            deck[month*4+2].type="素";

        deck[month*4+3].type="素";
    }


    FILE *fp=fopen("HanafudaRead.txt","r");

    fscanf(fp,"%c",&ch);
    while(!feof(fp))
    {
        putchar(ch);
        fscanf(fp,"%c",&ch);
    }
    fclose(fp);
    system("read");
    system("clear");

    while(restart=='Y')
    {
        tmp=startKoikoi(deck);
        point[0]+=tmp;
        point[1]-=tmp;

        printf("\n你的得分：%d",point[0]);
        printf("\n你对手的得分：%d",point[1]);
        printf("\n再来一局？（Y or N）:");
        getchar();
        scanf("%c",&restart);
    }

    return 0;
}

int startKoikoi(Card * deck)
{
    int round=0,turn,num,level,point[2]={0,0},lastPoint[2]={0,0},ifHandCombo[2]={0,0};
    char koikoi='Y';
    Card mountain[24],hand[2][8],table[3][32];

    shuffle(deck);

    for(int i=0;i<8;i++)
    {
        hand[0][i]=deck[i+24];
        hand[1][i]=deck[i+32];
        table[2][i]=deck[i+40];
    }
    for(int i=0;i<24;i++)
    {
        mountain[i]=deck[i];
        table[2][i+8].month=NULL;
    }

    for(int i=0;i<32;i++)
    {
        table[0][i].month=NULL;
        table[1][i].month=NULL;
    }

    printf("❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀\n");
    printf("❀Welcome to the world of Hanafuda⛩!!!\n");
    printf("❀请选择您想挑战的AI难度：\n\n");
    printf("❀1：傻子⛹\n");
    printf("❀2：正常人（暂不可用）⚖\n");
    printf("❀3：宗师（暂不可用）⚔⚔☭⚔⚔\n");
    scanf("%d",&level);
    while(level<1||level>1)
    {
        printf("\n输入错误！请重新输入您想挑战的AI难度：");
        scanf("%d",&level);
    }
    system("clear");

    while(round<16&&koikoi!='N')
    {
        printf("❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀\n");
        printf("\n❀你对手的手扎：");
        for(int i=0;i<8-(round+1)/2;i++)
            printf("▓ ");

        printf("\n❀你对手的场扎：\n");
        showOneTable(table[1],32,1);

        printf("\n\n❀山扎数量：%d\n",24-round);
        printf("❀场：\n");
        showOneTable(table[2],32,1);

        printf("\n\n❀你的场扎：\n");
        showOneTable(table[0],32,1);

        printf("\n❀你的手扎：\n");
        showOneTable(hand[0],8,1);

        if(!round)
        {
            if(checkHandCombo(hand[0]))
                ifHandCombo[0]=6;
            if(checkHandCombo(hand[1]))
                ifHandCombo[1]=6;
            if(point[0]&&!point[1])
            {
                if((koikoi=ifKoikoi(0))!='Y')
                    return 6;
                else
                    lastPoint[0]=6;
            }
            else if(point[1]&&!point[0])
            {
                printf("\n☠YOU LOST！☠");
                return -6;
            }
            else if(point[1]&&point[0])
            {
                printf("\n平局");
                return 0;
            }
        }
        printf("\n❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀第%d回合❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀",round+1);
        turn=round%2;
        if(turn)
        {
            num=round/2+1;
            printf("\n\n\n你的对手打出了：");
            showOneCard(hand[1],num-1);
            playOneCard(hand[1],table[2],table[1],num,level);
            Sleep(999);
            printf("\n你的对手翻开了：");
            showOneCard(mountain,round);
            playOneCard(mountain,table[2],table[1],round+1,level);
        }
        else
        {
            printf("\n\n请输入要打出的手扎编号：");
            scanf("%d",&num);
            while((!hand[0][num-1].month)||num<1||num>8)
            {
                printf("\n\n输入错误！请重新输入要打出的手扎编号：");
                scanf("%d",&num);
            }
            printf("\n你打出了：");
            showOneCard(hand[0],num-1);
            playOneCard(hand[0],table[2],table[0],num,0);
            system("read");
            printf("\n你翻开了：");
            showOneCard(mountain,round);
            playOneCard(mountain,table[2],table[0],round+1,0);\
        }
        point[turn]=checkTableCombo(table[turn],ifHandCombo[turn]);
        printf("\n总文数:%d文",point[turn]);
        if(point[turn]-lastPoint[turn])
            koikoi=ifKoikoi(turn);
        lastPoint[turn]=point[turn];
        Sleep(999);
        printf("\n❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀第%d回合结束❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀❀\n",++round);
        system("read");
        system("clear");
        //system("cls");
        //system("pause");
    }

    if(koikoi=='Y')
        if(point[0]==point[1])
            return 0;
        else
            return point[0]>point[1]?point[0]:(-point[1]);
    else
        return turn?(-point[1]):point[0];

}

void shuffle(Card * deck)
{
    Card tmp;
    for(int i=0,j;i<48;i++)
    {
        j=rand()%48;
        tmp=deck[i];
        deck[i]=deck[j];
        deck[j]=tmp;
    }
    for(int i=40,found=1;i<47&&found-4;i++)
    {
        found=1;
        for(int j=i+1;j<48;j++)
        {
            if(deck[i].month==deck[j].month)
                found++;
        }
        if(found==4)
            shuffle(deck);
    }
}

void showOneTable(Card * table,int max,int state)
{
    if(state)
    {
        char * type;
        for(int i=0,count=0;i<max;i++)
            if(table[i].month)
            {
                printf("%d⁜",i+1);
                showOneCard(table,i);
                count++;
                type=table[i].type;
                if(type=="素")
                    printf("   ");
                else if(type=="种"||type=="短")
                    printf(" ");
                printf("  ");
                if(!(count%6))
                    printf("\n");
            }
    }
    else
    {
        for(int i=0;i<max;i++)
            if(table[i].month)
            {
                showOneCard(table,i);
                printf("+");
            }
        printf("\b ");
    }
}

void showOneCard(Card * deck, int n)
{
    char * month=deck[n].month, * type=deck[n].type;
    if(type!="素")
        printf("「");
    printf("%s",month);//"松","梅","樱","藤","菖蒲","牡丹","萩","芒","菊","红叶","柳","桐"
    if(type=="短")
    {
        printf("に");
        if(month=="松"||month=="梅"||month=="樱")
            printf("赤短☰");
        else if(month=="牡丹"||month=="菊"||month=="红叶")
            printf("青短☷");
        else
            printf("短册");
    }
    else if(type=="种")
    {
        printf("に");
        if(month=="松")
            printf("鹤");
        else if(month=="梅")
            printf("莺");
        else if(month=="藤")
            printf("燕");
        else if(month=="菖蒲")
            printf("八桥");
        else if(month=="牡丹")
            printf("蝶");
        else if(month=="萩")
            printf("猪");
        else if(month=="芒")
            printf("雁");
        else if(month=="菊")
            printf("杯");
        else if(month=="红叶")
            printf("鹿");
        else if(month=="柳")
            printf("燕");
    }
    else if(type=="光")
    {
        printf("に");
        if(month=="松")
            printf("鹤");
        else if(month=="樱")
            printf("幕");
        else if(month=="芒")
            printf("月");
        else if(month=="柳")
            printf("小野道风");
        else if(month=="桐")
            printf("凤凰");
        printf("★");
    }
    else
        printf("-素");
    if(type!="素")
        printf("」");
}

void playOneCard(Card * hand,Card * table,Card * playertable,int num,int level)
{

    int tableNum=1,found=0,tmp[3];

    char * month=hand[num-1].month;

    for(int i=0;i<32;i++)
        if(table[i].month==month)
        {
            tmp[found]=i;
            found++;
        }

    if(found==2&&!level)
    {
        printf("\n请选择想要获得的场扎编号：1.");
        showOneCard(table,tmp[0]);
        printf("  2.");
        showOneCard(table,tmp[1]);
        printf("\n");
        scanf("%d",&tableNum);
        while(tableNum<1||tableNum>2)
        {
            printf("\n\n输入错误！请重新请选择想要获得的场扎编号：");
            scanf("%d",&tableNum);
        }
    }
    else
        tableNum=1;
    if(found)
    {
        int i=0;
        for(;playertable[i].month;i++);
        playertable[i]=hand[num-1];
        playertable[i+1]=table[tmp[tableNum-1]];
        table[tmp[tableNum-1]].month=NULL;
        if(found==3)
        {
            playertable[i+2]=table[tmp[1]];
            playertable[i+3]=table[tmp[2]];
            table[tmp[1]].month=NULL;
            table[tmp[2]].month=NULL;
        }

        printf("\n★你");
        if(level)
            printf("的对手");
        printf("获得了：");
        showOneCard(playertable,i);
        printf("  ");
        showOneCard(playertable,i+1);
        if(found==3)
        {
            printf("  ");
            showOneCard(playertable,i+2);
            printf("  ");
            showOneCard(playertable,i+3);
        }
    }
    else
    {
        int i=0;
        for(;table[i].month;i++);
        table[i]=hand[num-1];

        printf("\n☆你");
        if(level)
            printf("的对手");
        printf("失去了：");
        showOneCard(hand,num-1);
    }
    hand[num-1].month=NULL;
    printf("\n");
}

int checkHandCombo(Card * hand)
{
    Card handCheck[5][4];
    char * month;
    int point=0,i=0,count,countMax=0,countMaxNum,countCouple=0;
    for(;i<7;i++)
    {
        month=hand[i].month;
        count=0;
        handCheck[i][count]=hand[i];
        for(int j=i+1;j<8;j++)
            if(hand[j].month==month)
                handCheck[i][++count]=hand[j];
        if(countMax>count)
        {
            countMax=count;
            countMaxNum=i;
        }
        if(count==1)
        {
            countCouple++;
        }
        i++;
    }
    if(countMax==3)
    {
        showOneTable(handCheck[countMaxNum],4,0);
        printf("--> 6文役：「手四」！\n");
        return 1;
    }
    else if(countCouple==4)
    {
        for(i=0;i<4;i++)
        {
            showOneTable(handCheck[i],2,0);
            printf("+");
        }
        printf("\b--> 6文役：「四对」！\n");
        return 2;
    }
}

int checkTableCombo(Card * table,int ifHandCombo)
{
    int point=0,guangNum=0,zhongNum=0,duanNum=0,suNum=0;
    int guangYu=0,guangYue=0,guangHua=0,zhongZhuLuDie=0,zhongJiu=0,duanChi=0,duanQing=0;
    Card guang[5],zhong[9],duan[10],su[25];

    for(int i=0;table[i].month;i++)
        if(table[i].type=="光")
        {
            guang[guangNum++]=table[i];
            if(table[i].month=="柳")
                guangYu++;
            else if(table[i].month=="樱")
                guangHua++;
            else if(table[i].month=="芒")
                guangYue++;
        }
        else if(table[i].type=="种")
        {
            zhong[zhongNum++]=table[i];
            if(table[i].month=="萩"||table[i].month=="红叶"||table[i].month=="牡丹")
                zhongZhuLuDie++;
            else if(table[i].month=="菊")
                zhongJiu++;
        }
        else if(table[i].type=="短")
        {
            duan[duanNum++]=table[i];
            if(table[i].month=="松"||table[i].month=="梅"||table[i].month=="樱")
                duanChi++;
            else if(table[i].month=="牡丹"||table[i].month=="菊"||table[i].month=="红叶")
                duanQing++;
        }
        else
            su[suNum++]=table[i];

    printf("\n");
    if(ifHandCombo==1)
    {
        printf("6文手役：「手四」！\n");
        point+=6;
    }
    else if(ifHandCombo==2)
    {
        printf("6文手役：「四双」！\n");
        point+=6;
    }
    if(guangNum==5)
    {
        showOneTable(guang,5,0);
        printf("--> 10文役：「五★光」！！！\n");
        point+=10;
    }
    else if(guangNum==4&&guangYu)
    {
        showOneTable(guang,4,0);
        printf("--> 7文役：「雨四光」！\n");
        point+=7;
    }
    else if(guangNum==4)
    {
        showOneTable(guang,4,0);
        printf("--> 8文役：「四光」！\n");
        point+=8;
    }
    else if(guangNum==3&&!guangYu)
    {
        showOneTable(guang,3,0);
        printf("--> 6文役：「三光」！\n");
        point+=6;
    }
    if(guangHua&&zhongJiu)
    {
        printf("「樱に幕★」+「菊に杯」--> 5文役：「花见一杯」！\n");
        point+=5;
    }
    if(guangYue&&zhongJiu)
    {
        printf("「芒に月★」+「菊に杯」--> 5文役：「月见一杯」！\n");
        point+=5;
    }
    if(zhongZhuLuDie==3)
    {
        printf("「萩に猪」+「红叶に鹿」+「牡丹に蝶」--> 5文役：「猪鹿蝶」！\n");
        point+=5;
    }
    if(duanChi==3)
    {
        printf("「松に赤短☰」+「梅に赤短☰」+「樱に赤短☰」--> 5文役：「赤短」！\n");
        point+=5;
    }
    if(duanQing==3)
    {
        printf("「牡丹に青短☷」+「菊に青短☷」+「红叶に青短☷」--> 5文役：「青短」！\n");
        point+=5;
    }
    if(zhongNum>4)
    {
        showOneTable(zhong,zhongNum,0);
        printf("%d枚种扎--> %d文役：佳奈/タネ\n",zhongNum,zhongNum-4);
        point+=(zhongNum-4);
    }
    if(duanNum>4)
    {
        showOneTable(duan,duanNum,0);
        printf("%d枚短册扎--> %d文役：短册\n",duanNum,duanNum-4);
        point+=(duanNum-4);
    }
    if(suNum+zhongJiu>9)
    {
        printf("%d枚素扎--> %d文役：佳士/カス\n",suNum+zhongJiu,suNum+zhongJiu-9);
        point+=(suNum+zhongJiu-9);
    }

    if(point>7)
    {
        printf("「倍付」！");
        point+=point;
    }

    return point;
}

char ifKoikoi(int turn)
{
    char koikoi;
    if(!turn)
    {
        printf("\n\n❀こいこい？（Y or N）：");
        getchar();
        scanf("%c",&koikoi);
        if(koikoi!='N')
            printf("\n❀こいこい!!❀");
        else
            printf("\n❀や～めた!❀\n❀YOU WIN！❀");
    }
    else
    {
        printf("\n☠YOU LOSE！☠");
        koikoi='N';
    }
    return koikoi;
}
