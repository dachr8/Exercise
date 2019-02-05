#include <stdio.h>
   int main(void)
   {
      int a,b;
      char op;
      printf("输入一个数");
      scanf("%d",&a);
	  
	  printf("\n输入运算符:");
      scanf("%s",&op);

      printf("\n输入另一个数");
      scanf("%d",&b);

      switch(op)
      {
       case '+':
             printf("\n         =%d\n",a+b);
             break;
       case '-':
             printf("\n         =%d\n",a-b);
             break;
       case '*':
            printf("\n         =%d\n",a*b);
            break;
       case '/':
            printf("\n         =%d\n",a/b);
            break;
       default:
           break;
      } 
   }
