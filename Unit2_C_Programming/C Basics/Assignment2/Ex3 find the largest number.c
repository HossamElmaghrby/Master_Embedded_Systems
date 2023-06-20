/*
 ============================================================================
 Name        : Ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a=0,b=0,c=0;
	printf("Enter three number:\n");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&a,&b,&c);
	printf("Largest number =%0.2f ",(a>b)?(a>c)?a:c:(b>c)?b:c);
	return 0;
}
