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
#include <string.h>

int main(void) {

	char str[100],emp;
	int i=0,j;
	printf("Enter the string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	j=strlen(str)-1;

	while(i<j)
	{
	  emp=str[i];
	  str[i]=str[j];
	  str[j]=emp;
	  i++,j--;
	}
	printf("Reverse string: %s",str);
	return 0;
}
