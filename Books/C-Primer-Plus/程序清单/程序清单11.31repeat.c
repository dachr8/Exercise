//repeat.c--Main() with parameters
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("The command line has %d arguments:\n",argc-1);
    for (int i = 1; i < argc; ++i)
        printf("%d: %s\n",i,argv[i]);
    printf("\n");

    return 0;
}
