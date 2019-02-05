#include <stdio.h>
//Programming Exercise 4-5
//Prompt the user to enter the download speed in megabits per second and the file size in megabytes
int main(void)
{
    float speed,size;

    printf("Enter the download speed in megabits per second: ");
    scanf("%f",&speed);
    printf("Enter the file size in megabytes: ");
    scanf("%f",&size);
    printf("At %.2f megabits per second, a file of %.2f megabytes\n",speed,size);
    printf("downloads in %.2f seconds.",size*8/speed);

    return 0;
}
