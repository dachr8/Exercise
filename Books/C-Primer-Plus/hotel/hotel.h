#ifndef HOTEL_LIBRARY_H
#define HOTEL_LIBRARY_H

//hotel.h--Symbolic constants and prototypes for all functions in hotel.c
#define QUIT 5
#define HOTEL1 180.00
#define HOTEL2 225.00
#define HOTEL3 255.00
#define HOTEL4 355.00
#define DISCOUNT 0.95
#define STARS "***********************************"

//Display selection list
int menu(void);

//Return the scheduled number of days
int getNights(void);

//According to the rate, number of days of stay statistics costs and display the results
void showPrice(double rate,int nights);

#endif
