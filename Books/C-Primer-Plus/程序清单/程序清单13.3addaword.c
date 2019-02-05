//addaword.c -- Using fprintf(), fscanf() and rewind()
#include <stdio.h>
#include <stdlib.h>

#define MAX 47

int main(void) {
    FILE *fp;
    char words[MAX];
    int wordcnt = 0;

    if (!(fp = fopen("wordy", "a+"))) {
        fprintf(stdout, "Can't open \"wordy\" file.\n");
        exit(EXIT_FAILURE);
    }

    rewind(fp);
    while (fgets(words, MAX, fp))
        wordcnt++;
    rewind(fp);

    puts("Enter words to add to the file; press the #");
    puts("Key at the beginning of a line to terminate.");
    while ((fscanf(stdin, "%40s", words)) == 1 && (words[0] != '#'))
        fprintf(fp, "%3d: %s\n", ++wordcnt, words);

    puts("File contents:");
    rewind(fp);
    while (fgets(words, MAX, fp))
        puts(words);
    puts("Done!");
    if (fclose(fp))
        fprintf(stderr, "Error closing file\n");

    return 0;
}
