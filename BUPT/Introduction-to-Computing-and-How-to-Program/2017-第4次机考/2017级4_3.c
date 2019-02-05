#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getMaxSeqLen(char *s);

int main(void)
{
    char s[50];

    gets(s);

    printf("%d\n",getMaxSeqLen(s));

    return 0;
}

int getMaxSeqLen(char *s)
{
    int i=1,seqLen,len=strlen(s);
    if(!*(s+1))
        return 1;
    if(islower(*s))
    {
        while(islower(*(s+i))&&i<len)
            i++;
        s++;
        seqLen=getMaxSeqLen(s);
        return i>seqLen?i:seqLen;
    }
    else
    {
        while(isupper(*(s+i))&&i<len)
            i++;
        s++;
        seqLen=getMaxSeqLen(s);
        return i>seqLen?i:seqLen;
    }
}

