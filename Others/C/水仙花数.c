#include<stdio.h>
#include<math.h>
//水仙花数是指一个N位正整数（N≥3），它的每个位上的数字的N次幂之和等于它本身
//输入格式:输入在一行中给出一个正整数N（3≤N≤8）
//输出格式:按递增顺序输出所有N位水仙花数，每个数字占一行
int main(void)
{
    int N,copy_i,tmp,sum;

        scanf("%d",&N);
        for(int i=pow(10,N-1);i<pow(10,N);i++)
        {
            copy_i=i;
            sum=0;
            for(int j=0;j<N;j++)
            {
                tmp=copy_i%10;
                sum+=pow(tmp,N);
                copy_i/=10;
            }
            if(sum==i)
                printf("%d\n",i);
    }

    return 0;
}
