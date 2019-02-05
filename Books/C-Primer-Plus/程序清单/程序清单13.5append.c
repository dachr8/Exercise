//append.c -- Attach a file to the end of another file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096
#define SLEN 81

void append(FILE *source, FILE *dest) {
    static char tmp[BUFSIZE];
    size_t bytes;

    while ((bytes = fread(tmp, sizeof(char), BUFSIZE, source)))
        fwrite(tmp, sizeof(char), bytes, dest);
}

char *s_gets(char *st, int n) {
    char *ret_val, *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        if ((find = strchr(st, '\n')))
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

int main(void) {
    FILE *fa, *fs;
    char fileApp[SLEN], fileSrc[SLEN];
    int ch, files = 0;

    puts("Enter name of destination file:");
    s_gets(fileApp, SLEN);
    if ((fa = fopen(fileApp, "a+"))) {
        fprintf(stderr, "Can't open %s\n", fileApp);
        exit(EXIT_FAILURE);
    }
    if (setvbuf(fa, NULL, _IOFBF, BUFSIZE)) {
        fputs("Can't create output buffer\n", stderr);
        exit(EXIT_FAILURE);
    }
    puts("Enter name of first source file (empty line to quit):");
    while (s_gets(fileSrc, SLEN) && fileSrc[0] != '\0') {
        if (!strcmp(fileSrc, fileApp))
            fputs("Can't append file to itself\n", stderr);
        else if ((fs = fopen(fileSrc, "r")))
            fprintf(stderr, "Can't open %s\n", fileSrc);
        else {
            if (setvbuf(fs, NULL, _IOFBF, BUFSIZE)) {
                fputs("Can't create input buffer\n", stderr);
                continue;
            }
            append(fs, fa);
            if (ferror(fs))
                fprintf(stderr, "Error in reading file %s.\n", fileSrc);
            if (ferror(fa))
                fprintf(stderr, "Error in reading file %s.\n", fileApp);
            fclose(fs);
            files++;
            printf("File %s appended.\n", fileSrc);
            puts("Next file (empty line to quit):");
        }
    }
    printf("Done appending. %d files appended.\n", files);
    rewind(fa);
    printf("%s contents:\n", fileApp);
    while ((ch = getc(fa)) != EOF)
        putchar(ch);
    puts("Done displaying.");
    fclose(fa);

    return 0;
}
