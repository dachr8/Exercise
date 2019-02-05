#include "hotel.h"
//hotel.c--Hotel management functions
#include <stdio.h>

int menu(void)
{
    int code,status;

    printf("\n%s%s\n",STARS,STARS);
    printf("Enter the number of the desired hotel:\n");
    printf("1) Fairfield Arms         2) Hotel Olympic\n");
    printf("3) Chertworthy Plaza      4) The Stockton\n");
    printf("5) quit\n");
    printf("%s%s\n",STARS,STARS);
    while ((status=scanf("%d",&code))!=1||code<1||code>5)
    {
        if(status!=1)
            scanf("%*s");//Process non-integer inputs
        printf("Please enter an integer from 1 to 5.\n");
    }

    return code;
}

int getNights(void)
{
    int nights;

    printf("How many nights are needed? ");
    while(!scanf("%d",&nights))
    {
        scanf("%*s");
        printf("Please enter an integer, such as 2.\n");
    }

    return nights;
}

void showPrice(double rate,int nights)
{
    double total=0.0,factor=1.0;

    for (int n = 0; n < nights; ++n,factor*=DISCOUNT) {
        total+=rate*factor;
    }
    printf("The total cost will be $%0.2f.\n",total);
}
