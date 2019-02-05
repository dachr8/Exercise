#include <stdio.h>
#define ROW1 3
#define COL1 4
#define ROW2 4
#define COL2 3
void inputMatrix1(int matrix[][COL1],int rows,int cols);
void inputMatrix2(int matrix[][COL2],int rows,int cols);
void matrixMultiply(int matrix1[][COL1],int rows1,int cols1,int matrix2[][COL2],int cols2,int result[][COL2]);
void outputMatrix(int array[][COL2],int rows,int cols);
int main(void)
{
    int matrix1[ROW1][COL1], matrix2[ROW2][COL2],result[ROW1][COL2];//矩阵A的列数和矩阵B的行数相等,结果矩阵是ROW1行，COL2列

    printf("Please enter the first matrix(%d行%d列):\n",ROW1,COL1);
    inputMatrix1(matrix1,ROW1,COL1);
    printf("Please enter the second matrix(%d行%d列):\n",ROW2,COL2);
    inputMatrix2(matrix2,ROW2,COL2);

    matrixMultiply(matrix1,ROW1,COL1,matrix2,COL2,result);//矩阵相乘
    printf("Matrix multiplication result is:\n");
    outputMatrix(result,ROW1,COL2);

    return 0;
}

void inputMatrix1(int matrix[][COL1],int rows,int cols)
{
    for(int row=0;row<rows;row++)
        for(int col=0;col<cols;col++)
            scanf("%d",&matrix[row][col]);
}

void inputMatrix2(int matrix[][COL2],int rows,int cols)
{
    for(int row=0;row<rows;row++)
        for(int col=0;col<cols;col++)
            scanf("%d",&matrix[row][col]);
}

void matrixMultiply(int matrix1[][COL1],int rows1,int cols1,int matrix2[][COL2],int cols2,int result[][COL2])
{
    for(int row=0;row<rows1;row++) //目标矩阵有rows1行 cols2列
        for(int col=0;col<cols2;col++)//确定result[row][col]:matrix1的第row行和matrix2的第col列相乘
        {
            result[row][col]=0;
            for(int i=0;i<cols1;i++)
                result[row][col]+=matrix1[row][i]*matrix2[i][col];
        }
}

void outputMatrix(int matrix[][COL2],int rows,int cols)
{
    for(int row=0;row<rows;row++)
    {
        for(int col=0;col<cols; col++)
            printf("%d\t",matrix[row][col]);
        printf("\n");
    }
}
