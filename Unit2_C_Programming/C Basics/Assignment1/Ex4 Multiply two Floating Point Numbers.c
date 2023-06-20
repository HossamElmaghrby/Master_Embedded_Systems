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

int main(void) {
	float x=0,y=0;
	printf("Enter two number:\n");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&x,&y);
	printf("sum= %f",x*y);
	return 0;
}
