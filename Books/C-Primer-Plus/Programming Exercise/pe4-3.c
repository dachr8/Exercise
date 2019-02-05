#include <stdio.h>
//Programming Exercise 4-3
//Read a float
int main(void)
{
    float num;

    scanf("%f",&num);
    printf("%.1f\n",num);
    printf("%.1e\n",num);
    printf("%.3f\n",num);
    printf("%.3E\n",num);

    return 0;
}
