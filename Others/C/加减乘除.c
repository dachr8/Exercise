#include <stdio.h>
   int main(void)
   {
      int a,b;
      char op;
      printf("����һ����");
      scanf("%d",&a);
	  
	  printf("\n���������:");
      scanf("%s",&op);

      printf("\n������һ����");
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
