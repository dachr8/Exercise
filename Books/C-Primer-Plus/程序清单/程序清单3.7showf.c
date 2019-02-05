/*showf_pt.c--以两种方式显示float类型的值*/
#include<stdio.h>
     int main(void)
{
     float aboat=32000.0;
	 double abet=2.14e9;
	 long double dip=5.32e-5;
	 printf("%f can be written %e\n",aboat,aboat);
//下一行要求编译器支持C99或其中的相关特性
     printf("And it's %a in hexadecimal,powers of 2 notation\n",aboat);
	 printf("%f can be written %e\n",abet,abet);
	 printf("%Lf can be written %Le\n",dip,dip);
	 return 0;
}
//理论输出如下
//32000.000000 can be written 3.200000e+04
//And it's 0x1.f4p+14 in hexadecimal,powers of 2 notation
//2140000000.000000 can	be written 2.140000e+09
//0.000053 can be written 5.320000e-05

//实际输出如下
//32000.000000 can be written 3.200000e+004
//And it's 0x1.f40000p+14 in hexadecimal,powers of 2 notation
//2140000000.000000 can be written 2.140000e+009
//0.000000 can be written 3.205284e-317

//问题可能在于此编译器对ISO C99/C11及其功能的不支持上
