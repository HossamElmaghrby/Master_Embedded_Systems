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

void Revers_String(char str[])
{
	if(str[0]==NULL)
		return ;
	Revers_String(str+1);
	printf("%c",str[0]);
}
int main(void) {

   char str[100];
   printf("Enter a sentence :");
   fflush(stdin); fflush(stdout);
   gets(str);
   Revers_String(str);

	return 0;
}
