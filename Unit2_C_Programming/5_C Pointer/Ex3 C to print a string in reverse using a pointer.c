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
	char str[50];
	char *pstr;

	printf("Enter a string: ");
	fflush(stdout);
	scanf("%s",str);

	pstr=&str[strlen(str)-1];

	for(int i=0;i<strlen(str);i++)
	{
		printf("%c",*pstr);
		pstr--;
	}
	return EXIT_SUCCESS;
}
