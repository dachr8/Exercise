#include<stdio.h>

int getWeekDay(int year,int month,int day);
int getMonthDays(int year,int month);
void printMonthCalender(int startDay,int days);

int main(void)
{
    int year,month,startDay,monthDays;

    printf("Please input the year (and month):");
    scanf("%d",&year);
    printf("\nThe result is:");
    if(getchar()=='\n')
        for(int month=1;month<13;month++)
        {
            startDay=getWeekDay(year,month,1);//计算出该月第一天是星期几。返回值为0～6，分别代表周日，周一～周六
            monthDays=getMonthDays(year,month);//计算出该月共有几天
            printf("\n\t\t\t%d-%d\n",year,month);
            printMonthCalender(startDay,monthDays);
        }
    else
    {
        scanf("%d",&month);
        startDay=getWeekDay(year,month,1);//计算出该月第一天是星期几。返回值为0～6，分别代表周日，周一～周六
        monthDays=getMonthDays(year,month);//计算出该月共有几天
        printf("\n\t\t\t%d-%d\n",year,month);
        printMonthCalender(startDay,monthDays);
    }

    return 0;
}

int getWeekDay(int year,int month,int day)
{
    int daysY=(year-1)*365+(year-1)/400+(year-1)/4-(year-1)/100;;//从0001年到year－1年共有几天
    int daysM=0;//从year年1月到month－1月共有几天

    for(int i=1;i<month;i++)
        daysM+=getMonthDays(year,i);//第二次用到该函数

    return (daysY+daysM+day)%7;//公元第一天是周一
}

int getMonthDays(int year,int month)
{
    switch(month)
    {
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            return 31;
        case 4:case 6:case 9:case 11:
            return 30;
        case 2:
            if ((year%100)?!(year%4):!(year%400))
                return 29;//闰年
            else
                return 28;
        default:
            break;
    }
}

void printMonthCalender(int startDay,int days)
{
    int i,count=startDay;//控制换行

    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");//打印表头
    for(i=0;i<startDay;i++)//打印前面空格
        printf("\t");
    for(i=1;i<=days;i++)
    {
        printf("%d",i);
        count++;
        if(count%7!=0)
            printf("\t");
        else
            printf("\n");
    }
    printf("\n");
}
