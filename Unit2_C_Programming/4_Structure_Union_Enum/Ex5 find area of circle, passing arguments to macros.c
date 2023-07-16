/*
 ============================================================================
 Name        : Ex5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define pi 3.1415
#define area(r)(pi*r*r)
int main(void) {
	int radius;
	float area;
	printf("Enter the radius: ");
	fflush(stdout);
	scanf("%d",&radius);
	area=area(radius);
	printf("Area=%0.2f",area);

	return EXIT_SUCCESS;
}
