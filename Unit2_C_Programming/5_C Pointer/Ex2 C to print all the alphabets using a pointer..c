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
	char c='A';
    char *alph=&c;
    do
	{
		printf("%c ",*alph);
		(*alph)++;
	}while(*alph!='Z');
    printf("%c ",*alph);
	return EXIT_SUCCESS;
}
