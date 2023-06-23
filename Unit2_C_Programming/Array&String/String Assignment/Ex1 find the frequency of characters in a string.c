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
	char str[100],ch;
	int count=0;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);

	gets(str);

	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&ch);

	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]==ch)
			++count;
	}

	printf("frequency of %c= %d",ch,count);
	return EXIT_SUCCESS;
}
