//diceroll.c -- Rolling dice simulator

#include "diceroll.h"
#include <stdio.h>
#include <stdlib.h>

int rollCount = 0;

static int rollem(int sides) {
    rollCount++;
    return rand() % sides + 1;
}

int rollNDice(int dice, int sides) {
    if (sides < 2) {
        printf("Need at least 2 sides.\n");
        return -2;
    } else if (dice < 1) {
        printf("Need at least 1 sides.\n");
        return -1;
    } else {
        int total = 0;
        for (int i = 0; i < dice; ++i)
            total += rollem(sides);
        return total;
    }
}
