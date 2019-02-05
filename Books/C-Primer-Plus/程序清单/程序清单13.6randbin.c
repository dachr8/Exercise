//randbin.c -- Random access with binary I/O
#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 1000

int main(void) {
    double numbers[ARSIZE], value;
    const char *file = "numbers.dat";
    long pos;
    FILE *iofile;

    for (int i = 0; i < ARSIZE; ++i)
        numbers[i] = 100 * i + 1.0 / (i + 1);

    if ((iofile = fopen(file, "wb")) == NULL) {
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(EXIT_FAILURE);
    }

    fwrite(numbers, sizeof(double), ARSIZE, iofile);
    fclose(iofile);
    if ((iofile = fopen(file, "rb")) == NULL) {
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(EXIT_FAILURE);
    }

    printf("Enter an index in the range 0-%d.\n", ARSIZE - 1);
    while (scanf("%ld", &pos) == 1 && pos >= 0 && pos < ARSIZE) {
        fseek(iofile, pos * sizeof(double), SEEK_SET);
        fread(&value, sizeof(double), (size_t) pos, iofile);
        printf("The value there is %f.\n", value);
        puts("Next index (out of range to quit)");
    }

    fclose(iofile);
    puts("Bye!");

    return 0;
}
