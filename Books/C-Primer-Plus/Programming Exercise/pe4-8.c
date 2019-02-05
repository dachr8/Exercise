#include <stdio.h>
#define gallon_liter 3.785
#define mile_kilometer 1.609
//Programming Exercise 4-8
int main(void)
{
    double mileage,gasline;
    const double k=gallon_liter/mile_kilometer/100;

    printf("Enter the mileage of the trip: ");
    scanf("%lf",&mileage);
    printf("Enter the amount of gasoline consumed: ");
    scanf("%lf",&gasline);
    printf("Consume miles per gallon of gas: %.1lf\n",mileage/gasline);
    printf("Consume 100 kilometers per liter of gasoline: %.1lf\n",k*gasline/mileage);

    return 0;
}
