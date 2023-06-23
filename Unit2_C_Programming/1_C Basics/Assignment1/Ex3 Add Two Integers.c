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

	int x=0,y=0;
	printf("Enter two number:\n");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	printf("sum= %d",x+y);
	return 0;
}
