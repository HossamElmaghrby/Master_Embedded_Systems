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

int main(void) {
	char str[1000];
	int i;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",str);
	for(i=0;str[i]!='\0';i++);
	printf("length of string:%d",i);
	return EXIT_SUCCESS;
}
