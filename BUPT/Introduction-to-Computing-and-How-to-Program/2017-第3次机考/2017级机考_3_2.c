#include <stdio.h>

//2017-计算机导论与程序设计-第3次机考
//B. 2017级机考_3_2
//1.一个由大写字母组成的字符串，如果该字符串只由’A’、’B’和’C’组成，并且存在一个长度为3的“连续子串”，那么这个字符串就是纯净的，否则这个字符串就是暗黑的。
//例如：BAACAACCBAAA 只由’A’,’B’,’C’组成，并且存在连续子串”CBA”，所以是纯净的；
//字符串AABBCCAABB不存在一个长度为3的连续子串，字符串HELLOABC包含非’A’、’B’、’C’字母，所以它们都是暗黑的字符串。
//任务：输入一个由大写字母组成的字符串，判断是不是纯净的字符串。
//2.假设用户输入肯定正确，程序不需要对异常输入进行处理。请写出完整C语言程序。
//3.本题不能使用数组，否则视为0分处理
//输入与输出说明：
//第一行：一个大写字母组成的字符串，以换行符’\n’结束。
//第二行：输出判断结果，如果是纯净的，返回true，否则返回false，换行结束。

int main(void)
{
    char ch1,ch2,ch3;
    int flag=1;

    ch1=getchar();
    ch2=getchar();
    ch3=getchar();
    if(ch1<'A'||'C'<ch1||ch2<'A'||'C'<ch2||ch3<'A'||'C'<ch3)
        flag=2;
    while(ch3!='\n'&&flag!=2)
    {
        if(ch1!=ch2&&ch1!=ch3&&ch2!=ch3)
            flag=0;
        if(ch3<'A'||'C'<ch3)
            flag=2;
        ch1=ch2;
        ch2=ch3;
        ch3=getchar();
    }
    if(flag)
        printf("false");
    else
        printf("true");

    return 0;
}
