//r_drive1.c -- Test the rand1() and srand1()
//Compiled with s_and_r.c
#include <stdio.h>
#include <stdlib.h>

extern void srand1(unsigned int x);

extern int rand1(void);

int main(void) {
    unsigned seed;

    printf("Please enter your choice for seed.\n");
    while (scanf("%u", &seed) == 1) {
        srand1(seed);
        for (int i = 0; i < 5; ++i)
            printf("%d\n", rand1());
        printf("Please enter next seed (q to quit):\n");
    }
    printf("Done\n");

    return 0;
}
