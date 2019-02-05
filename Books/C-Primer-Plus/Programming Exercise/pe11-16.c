//Programming Exercise 11-16
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int ch;
    char mode='p';
    _Bool ok=1;

    if(argc>2)
    {
        printf("Usage: %s [-p | -u | -l]\n",argv[0]);
        ok=0;
    }
    else if(argc==2)
    {
        if(argv[1][0]!='-')
        {
            printf("Usage: %s [-p | -u | -l]\n",argv[0]);
            ok=0;
        }
        else
            switch (argv[1][1])
            {
                case 'p':
                case 'u':
                case 'l':mode=argv[1][1];
                    break;
                default:printf("%s is an invalid flag;,argv[1]");
                    printf("using default flag (-p).\n");
            }
    }
    if(ok)
        while ((ch=getchar())!=EOF)
            switch (mode)
            {
                case 'p':putchar(ch);
                    break;
                case 'u':putchar(toupper(ch));
                    break;
                case 'l':putchar(tolower(ch));
                default:printf("BUG");
            }

    return 0;
}
