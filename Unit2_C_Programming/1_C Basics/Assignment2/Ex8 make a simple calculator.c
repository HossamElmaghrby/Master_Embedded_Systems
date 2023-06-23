/*
 ============================================================================
 Name        : Ex8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a=0,b=0,res=0;
	char x;

	printf("Enter the operator: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	printf("Enter the two number:\n");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&a,&b);

	switch(x)
	{
    case '+':
	 res=a+b;
	 break;

    case '-':
	 res=a-b;
	 break;

    case '*':
	 res=a*b;
	 break;

   case '/':
	 res=a/b;
	 break;

   default:
	   printf("incorrect operator");
	}

	printf("%0.2f %c %0.2f = %0.2f\n",a,x,b,res);
	main();
	return 0;

}
