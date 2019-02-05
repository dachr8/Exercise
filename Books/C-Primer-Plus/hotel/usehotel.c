#include <stdio.h>
#include "hotel.h"
//usehotel.c--Room rate program
//Compile with hotel.c
int main(void)
{
    int nights,code;
    double hotelRate;

    while ((code=menu())!=QUIT)
    {
        switch (code)
        {
            case 1:hotelRate=HOTEL1;
                break;
            case 2:hotelRate=HOTEL2;
                break;
            case 3:hotelRate=HOTEL3;
                break;
            case 4:hotelRate=HOTEL4;
                break;
            default:hotelRate=0.0;
                printf("Oop!\n");
                break;

        }
        nights=getNights();
        showPrice(hotelRate,nights);
    }
    printf("Thank you and goodbye,\n");

    return 0;
}
