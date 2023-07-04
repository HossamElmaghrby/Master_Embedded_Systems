/*
 ============================================================================
 Name        : Ex4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int power(int base , int pow)
{
	if(pow==0)
		return 1;
	return base*power(base,--pow);
}
int main(void) {

	int base, pow;

	printf("Enter base: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&base);
	printf("Enter power number(positive integer): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&pow);

	printf("%d^%d= %d",base,pow,power(base,pow));
	return EXIT_SUCCESS;
}
