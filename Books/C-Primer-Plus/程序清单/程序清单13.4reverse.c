//reverse.c -- Display the contents of the file in reverse order
#include <stdio.h>
#include <stdlib.h>

#define CNTL_Z '\032'
#define SLEN 81

int main(void) {
    char file[SLEN];
    FILE *fp;

    puts("Enter the name of the file to be processed:");
    scanf("%80s", file);
    if ((fp = fopen(file, "rb")) == NULL) {
        printf("reverse can't open %s\n", file);
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long last = ftell(fp);
    for (long i = 1; i < last; ++i) {
        fseek(fp, -i, SEEK_END);
        int ch = getc(fp);
        if (ch != CNTL_Z && ch != '\r')
            putchar(ch);
    }
    putchar('\n');
    fclose(fp);

    return 0;
}
