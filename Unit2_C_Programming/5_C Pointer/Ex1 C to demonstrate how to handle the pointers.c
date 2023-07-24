/*
 ============================================================================
 Name        : Ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int m=29;
	printf("Address of m: 0x%x\n",(unsigned int)&m);
	printf("Value of m: %d\n",m);

	int *ab=&m;
	printf("\nNow ab is assigned with the address of m.\n");
	printf("Address of ab: 0x%x\n",(unsigned int)ab);
	printf("Value of ab: %d\n",*ab);

	m=34;
	printf("\nThe value of m assigned to 34 now.\n");
	printf("Address of ab: 0x%x\n",(unsigned int)ab);
	printf("Value of ab: %d\n",*ab);

	*ab=7;
	printf("\nThe pointer variable ab is assigned with the value 7 now.\n");
	printf("Address of m: 0x%x\n",(unsigned int)&m);
	printf("Value of m: %d\n",m);

	return EXIT_SUCCESS;
}
