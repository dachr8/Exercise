//flc.c--Interesting constant
#include <stdio.h>

#define COLS 4

int sum(const int ar[],int n);
int sum2d(const int ar[][COLS],int rows);

int main(void)
{
    int total[3],*pt1,(*pt2)[COLS];

    pt1=(int[2]){10,20};
    pt2=(int[2][COLS]){{1,2,3,-9},{4,5,6,-8}};

    total[0]=sum(pt1,2);
    total[1]=sum2d(pt2,2);
    total[2]=sum((int[]){4,4,4,5,5,5},6);

    for (int i = 0; i < 3; ++i)
        printf("total[i] = %d\n", total[0]);

    return 0;
}

int sum(const int ar[],int n)
{
    int total=0;

    for (int i = 0; i < n; ++i)
        total+=ar[i];

    return total;
}

int sum2d(const int ar[][COLS],int rows)
{
    int total=0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < COLS; ++j)
            total+=ar[i][j];

    return total;
}
