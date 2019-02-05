//hello.c--Convert command line arguments to numbers
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int times;

    if(argc<2||(times=atoi(argv[1]))<1)
        printf("Usage: %s positive-number\n",argv[0]);
    else
        for (int i = 0; i < times; ++i)
            puts("Hello, good looking!");

    return 0;
}
