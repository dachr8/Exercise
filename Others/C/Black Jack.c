#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void shuffle (int [][13]);
void showOneCard(const int deck[][13],int card);
int check(const int deck[][13],int playerAcard,int playerBcard);
void result(const int deck[][13],int playerAcard,int playerBcard);
int Card(const int deck[][13],int card);
//void deal(const int [][13]);
//void outputCard(int i,int row,int col);

int main(void)
{
    int deck[4][13]={0},playerAcard=2,playerBcard=2,checkFlag=0;
    char another='Y';

    while(another=='Y')
    {
        printf("\n\nWelocome to Black Jack!\n\n");
        srand(time(NULL));
        shuffle(deck);//洗牌//deal(deck);//发牌
        printf("Your opponent has two cards: a ");
        showOneCard(deck,21);
        printf(" and a unknown card.\n");

        while(another=='H')
        {
            printf("\n\nNow you have %d cards: a ",playerAcard++);
            for(int i=2;i<playerAcard;i++)
            {
                showOneCard(deck,i+9);
                printf(" and a ");
            }
            showOneCard(deck,playerAcard+9);
            printf(".\n\n");
            checkFlag=check(deck,playerAcard-1,playerBcard);
            if(!checkFlag)
            {
                printf("Hit or stand? ( H or S)\n");
                scanf("%c",&another);
                getchar();
            }
            else
                another=' ';
        }
        printf("\nThe unknown card is a ");
        showOneCard(deck,12);
        printf(".\n\n");
        if(!checkFlag)
            result(deck,playerAcard-1,playerBcard);
        printf("\nPlay again?( Y or N)\n");
        scanf("%c",&another);
        getchar();
    }

    return 0;
}

void shuffle(int deck[][13])//洗牌
{
    int row,col;

    for(int card=1;card<53;card++)//生成第card张牌的花色和面值
    {
        row=rand()%4;
        col=rand()%13;
        while(deck[row][col])
        {
            row=rand()%4;
            col=rand()%13;
        }//发出第card张牌
        deck[row][col]=card;
    }
}

void showOneCard(const int deck[][13],int card)
{
    for (int row=0;row<4;row++)//遍历二维数组，查找值为card的元素，输出对应的花色和面值
        for (int col=0;col<13;col++)
            if(deck[row][col]==card)
            {
                switch (col)
                {
                    case 0:printf("Acer");break;
                    case 1:printf("Deuce");break;
                    case 2:printf("Three");break;
                    case 3:printf("Four");break;
                    case 4:printf("Five");break;
                    case 5:printf("Six");break;
                    case 6:printf("Seven");break;
                    case 7:printf("Eight");break;
                    case 8:printf("Nine");break;
                    case 9:printf("Ten");break;
                    case 10:printf("Jack");break;
                    case 11:printf("Queen");break;
                    case 12:printf("King");break;
                    default:printf("无效的面值 !");
                }
                printf(" of ");
                switch (row)
                {
                    case 0:printf("Hearts");break;
                    case 1:printf("Diamonds");break;
                    case 2:printf("Clubs");break;
                    case 3:printf("Spades");break;
                    default:printf("无效的花色 !");
                }
                return;
            }
}

int check(const int deck[][13],int playerAcard,int playerBcard)
{
    int playerApoints=0,playerBpoints=0;

    for(int i=0;i<playerAcard;i++)
        playerApoints+=Card(deck,i+11);
    for(int i=0;i<playerBcard;i++)
        playerBpoints+=Card(deck,i+21);

    if(playerApoints>22)
        for(int i=0;i<playerAcard;i++)
            if(Card(deck,i+11)==11&&playerApoints>22)
                playerApoints-=10;
    if(playerBpoints>22)
        for(int i=0;i<playerBcard;i++)
            if(Card(deck,i+11)==11&&playerBpoints>22)
                playerBpoints-=10;
    if(playerApoints==21&&playerBpoints<21)
    {
        printf("Black Jack!!!\n\n");
        printf("You win!!!");
        return 1;
    }
    else if(playerBpoints==21&&playerApoints<21)
    {
        printf("Black Jack!!!\n\n");
        printf("Your opponent win!!!");
        return 1;
    }
    else if(playerBpoints==21&&playerApoints==21)
    {
        printf("Double Black Jack!!!\n\n");
        printf("Push!!!");
        return 1;
    }
    else if(playerBpoints>21&&playerApoints<22)
    {
        printf("Your opponent's point is %d(>21).\n",playerBpoints);
        printf("Bust!!!\n\n");
        printf("You win!!!");
        return 1;
    }
    else if(playerApoints>21&&playerBpoints<22)
    {
        printf("Your point is %d(>21).\n",playerApoints);
        printf("Bust!!!\n\n");
        printf("Your opponent win!!!");
        return 1;
    }
    else if(playerBpoints>21&&playerApoints>21)
    {
        printf("Your point is %d(>21).\n",playerApoints);
        printf("Your opponent's point is %d(>21).\n",playerBpoints);
        printf("Double Bust!!!\n\n");
        printf("Push!!!");
        return 1;
    }

    return 0;
}

void result(const int deck[][13],int playerAcard,int playerBcard)
{
    int playerApoints=0,playerBpoints=0;

    for(int i=0;i<playerAcard;i++)
        playerApoints+=Card(deck,i+11);
    for(int i=0;i<playerBcard;i++)
        playerBpoints+=Card(deck,i+21);
    printf("Your point is %d.\n",playerApoints);
    printf("Your opponent's point is %d.\n",playerBpoints);
    if(playerApoints>playerBpoints)
        printf("You win!!!");
    else if(playerApoints<playerBpoints)
        printf("Your opponent win!!!");
    else
        printf("Push!!!");
}

int Card(const int deck[][13],int card)
{
    for (int row=0;row<4;row++)//遍历二维数组，查找值为card的元素，输出对应的花色和面值
        for (int col=0;col<13;col++)
            if(deck[row][col]==card)
            {
                if(col>9)
                    col=9;
                if(!col)
                    col=10;
                return col+1;
            }
}

void deal(const int deck[][13]) //发牌
{
    int found;

    for(int card=1;card<53;card++)
    {
        found=0;//遍历二维数组，查找值为card的元素，输出对应的花色和面值
        for(int row=0;row<4&&!found;row++)
            for(int col=0;col<13&&!found;col++)
                if(deck[row][col]==card)
                {
                    found=1;
                    outputCard(card,row,col); //输出第card张牌的花色面值
                }
    }
}

void outputCard(int i,int row,int col)
{
    printf("第%d张牌：",i);
    switch (col)
    {
        case 0:printf("Acer");break;
        case 1:printf("Deuce");break;
        case 2:printf("Three");break;
        case 3:printf("Four");break;
        case 4:printf("Five");break;
        case 5:printf("Six");break;
        case 6:printf("Seven");break;
        case 7:printf("Eight");break;
        case 8:printf("Nine");break;
        case 9:printf("Ten");break;
        case 10:printf("Jack");break;
        case 11:printf("Queen");break;
        case 12:printf("King");break;
        default:printf("无效的面值 !");
    }
    printf(" of ");
    switch (row)
    {
        case 0:printf("Hearts");break;
        case 1:printf("Diamonds");break;
        case 2:printf("Clubs");break;
        case 3:printf("Spades");break;
        default:printf("无效的花色 !");
    }
    printf("\n");
}
