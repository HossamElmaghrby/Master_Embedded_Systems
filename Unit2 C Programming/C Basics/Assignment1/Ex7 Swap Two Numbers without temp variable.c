/*
 ============================================================================
 Name        : Ex7.c
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
	printf("X=");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x);
	printf("Y=");
	fflush(stdin); fflush(stdout);
	scanf("%f",&y);

	x+= y;
	y=x-y;
	x=x-y;
	printf("-----After swapping-----\n"
			"X=%.2f\nY=%.2f",x,y);
	return 0;
}
