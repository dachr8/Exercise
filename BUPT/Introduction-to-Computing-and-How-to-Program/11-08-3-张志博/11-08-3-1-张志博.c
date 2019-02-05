//1. Problem 1 of Experiment 12 (First time ASCII code file)
#include <stdio.h>
#include <ctype.h>

void printTask1(int cap, int low, int dig, int oth) {
    printf("Task1:\n");
    printf("capital:%d\n", cap);
    printf("lowercase:%d\n", low);
    printf("digit:%d\n", dig);
    printf("others:%d\n\n", oth);
}

void printTask2(int line, int max, int min) {
    printf("Task2:\n");
    printf("line:%d\n", line);
    printf("%d characters in max line.\n", max);
    printf("%d characters in min line.\n\n", min);
}

void printTask3(int capital[], int lowercase[]) {
    printf("Task3:\n");
    printf("CAPITAL:\n");
    for (int i = 0; i < 26; ++i)
        printf("%c:%d%c", 'A' + i, capital[i], (i + 1) % 4 ? '\t' : '\n');
    printf("\nLOWERCASE:\n");
    for (int i = 0; i < 26; ++i)
        printf("%c:%d%c", 'A' + i, lowercase[i], (i + 1) % 4 ? '\t' : '\n');
}

int main(void) {
    int cap = 0, low = 0, dig = 0, oth = 0;
    int line = 1, max = 0, min = -1, characters = 0;
    int capital[26] = {0}, lowercase[26] = {0};

    FILE *fp = fopen("p1.txt", "r");

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        characters++;
        if (isupper(ch)) {
            cap++;
            capital[ch - 'A']++;
        } else if (islower(ch)) {
            low++;
            lowercase[ch - 'a']++;
        } else if (isdigit(ch))
            dig++;
        else {
            oth++;
            if (ch == '\n') {
                line++;
                characters -= 2;//In the Windows system, the end of each line is "<enter><line break>", ie "\r\n"
                max = max > characters ? max : characters;
                min = min == -1 ? characters : (min < characters ? min : characters);
            }
        }
    }
    max = max > characters ? max : characters;
    min = min == -1 ? characters : (min < characters ? min : characters);

    fclose(fp);
    printf("The result is:\n");
    printTask1(cap, low, dig, oth);
    printTask2(line, max, min);
    printTask3(capital, lowercase);

    return 0;
}
