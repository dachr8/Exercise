//partb.c --- Other parts of the program
//Compile with parta.c
#include <stdio.h>

extern int count;      //Quote statement, external link

static int total = 0;  //Static definition, internal links

void accumulate(int k) //k has block scope, no link
{
    static int subtotal = 0;//Static, no link

    if (k <= 0) {
        printf("loop cycle: %d\n", count);
        printf("subtotal: %d; total: %d\n", subtotal, total);
        subtotal = 0;
    } else {
        subtotal += k;
        total += k;
    }
}
