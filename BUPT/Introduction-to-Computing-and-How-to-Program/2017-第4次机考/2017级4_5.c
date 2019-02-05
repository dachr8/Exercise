#include <stdio.h>
/*
8
1 -1 2 -3 4 -5 6 -7

5
1 6 3 6 4

6
1 6 3 4 4 6

4
1 5 3 4
*/
//LIS to LCS
int main(void)
{
    int len;

    scanf("%d",&len);

    int Slen=len,array[len],sort[len];

    for(int i=0;i<len;i++)
    {
        scanf("%d",&array[i]);
        sort[i]=array[i];
    }

    for(int i=0,tmp;i<len;i++)
        for(int j=0;j<Slen-1;j++)
            if(sort[j]>sort[j+1])
            {
                tmp=sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=tmp;
            }
            else if(sort[j]==sort[j+1])
            {
                for(int k=j+1;k<len-1;k++)
                    sort[k]=sort[k+1];
                Slen--;
            }

    int matrix[len+1][Slen+1],mark[len+1][Slen+1];

    for (int i=0;i<=len;i++)
        for(int j=0;j<=Slen;j++)
        {
            matrix[i][j]=0;
            mark[i][j]=0;
        }

    for(int i=0;i<len;i++)
        for(int j=0;j<Slen;j++)
            if(array[i]==sort[j])
            {
                matrix[i+1][j+1]=matrix[i][j]+1;
                mark[i+1][j+1]=1;//c[i][j]是由c[i-1][j-1]+1来
            }
            else if(matrix[i][j+1]>=matrix[i+1][j])
            {
                matrix[i+1][j+1]=matrix[i][j+1];
                mark[i+1][j+1]=2;//c[i][j]是由c[i-1][j]来
            }
            else
            {
                matrix[i+1][j+1]=matrix[i+1][j];
                mark[i+1][j+1]=3;//c[i][j]是由c[i][j-1]来
            }

    int longest=matrix[len][Slen],result[longest];
    printf("The number of the LIS is: %d\n",longest);

    for(int i=len,j=Slen,k=longest;i&&j;)
        if(mark[i][j]==1)
        {
            result[--k]=array[--i];
            j--;
        }
        else if(mark[i][j]==2)
            i--;
        else
            j--;

    for(int i=0;i<longest-1;i++)
        printf("%d ",result[i]);
    printf("%d\n",result[longest-1]);

    return 0;
}