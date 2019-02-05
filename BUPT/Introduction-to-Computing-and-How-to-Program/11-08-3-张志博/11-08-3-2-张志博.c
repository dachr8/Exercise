//2. Problem 4 of Experiment 12 (Comment filter)
#include <stdio.h>

void CommentFilter(FILE *in, FILE *out) {

    int ch1 = 0, ch2, status = 0;
    while ((ch2 = fgetc(in)) != EOF) {
        if (status == 1) {
            if (ch2 == '\n') {
                fputc('\n', out);
                status = 0;
            }
        } else if (status == 2) {
            if (ch1 == '*' && ch2 == '/') {
                status = 0;
                ch2 = 0;
            }
        } else if (status == -1)//To be able to handle printf // or /**/
        {
            putc(ch2, out);
            if (ch2 == '\"')
                status = 0;
        } else if (ch2 == '\"') {
            if (ch1 != '\\') {
                status = -1;
                fputc('\"', out);
            }

        } else if (ch2 == '/') {
            if (ch1 == '/')
                status = 1;
        } else if (ch1 == '/' && ch2 == '*') {
            status = 2;
            ch2 = 0;
        } else {
            if (ch1 == '/')
                fputc('/', out);
            fputc(ch2, out);
        }
        ch1 = ch2;
    }

}

int main(void) {
    FILE *in = fopen("p2in.c", "r");
    FILE *out = fopen("p2out.c", "w");

    CommentFilter(in, out);

    fclose(in);
    fclose(out);

    return 0;
}
