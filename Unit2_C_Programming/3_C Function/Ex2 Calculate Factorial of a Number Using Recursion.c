/*
 ============================================================================
 Name        : Ex2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

long int factorial(int n)
{
	if(n==0)
		return 1;

	return factorial(n-1)*n;
}
int main(void) {

	int x;
	printf("Enter an positive integer: ");
	fflush(stdin); fflush(stdout);
     scanf("%d",&x);
     printf("factorial of %d = %ld",x,factorial(x));
	return 0;
}
