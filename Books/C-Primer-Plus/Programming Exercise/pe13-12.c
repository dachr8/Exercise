#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 30
#define LEVELS 10
const char trans[LEVELS + 1] = " .':~*=&%@";


void init(char arr[][COLS], char ch) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            arr[i][j] = ch;
}

void makePic(int data[][COLS], char pic[][COLS], int rows) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < COLS; ++j)
            pic[i][j] = trans[data[i][j]];
}

int main(void) {
    int picIn[ROWS][COLS];
    char picOut[ROWS][COLS], fileName[81];
    FILE *infile;

    init(picOut, 'S');

    puts("Enter name of file: ");
    scanf("%80s", fileName);
    if (!(infile = fopen(fileName, "r"))) {
        fputs("Could not open data file.", stderr);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            fscanf(infile, "%d", &picIn[i][j]);
    if (ferror(infile)) {
        fputs("Error getting datd from file.", stderr);
        exit(EXIT_FAILURE);
    }
    makePic(picIn, picOut, ROWS);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j)
            putchar(picOut[i][j]);
        putchar('\n');
    }

    return 0;
}
