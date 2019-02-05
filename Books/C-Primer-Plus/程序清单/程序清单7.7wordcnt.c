#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define STOP '|'
//wordcnt.c--count characters, words, lines
int main(void)
{
    char c,prev='\n';
    int nChars=0,nLines=0,nWords=0;
    bool inword=false,pLines=false;

    printf("Enter text to be analyzed (| to terminate):\n");
    while((c=getchar())!=STOP)
    {
        nChars++;
        if(c=='\n')
            nLines++;
        else if(!isspace(c)&&!inword)
        {
            inword=true;
            nWords++;
        }
        else if(isspace(c)&&inword)
            inword=false;
        prev=c;
    }
    if(prev!='\n')
        pLines=true;

    printf("characters = %d, words = %d, lines = %d, partial lines = %d\n",nChars,nWords,nLines,pLines);

    return 0;
}
