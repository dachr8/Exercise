#include <stdio.h>
//第2题. 实验手册中实验1的第2题 (基本类型数据的输入和输出)
int main(void)
{
    char sex;
    int age;
    float height;
    printf("Please input sex:");
    scanf("%c",&sex);
    printf("Please input age:");
    scanf("%d",&age);
    printf("Please input height:");
    scanf("%f",&height);
    printf("The sex is %c, the age is %d, and the height is %f.",sex,age,height);
    return 0;
}
