//count.c -- Using standard I/O
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int ch;
    unsigned long count = 0;
    while ((ch = getc(fp)) != EOF) {
        putc(ch, stdout);
        ++count;
    }
    fclose(fp);

    printf("File %s has %lu characters\n", argv[1], count);

    return 0;
}
