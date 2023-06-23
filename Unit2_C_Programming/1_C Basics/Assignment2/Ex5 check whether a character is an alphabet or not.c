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

int main(void) {
	char x;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	if((x >= 'a' && x <= 'z')||(x >= 'A'&& x <= 'Z'))
		printf("%c is an alphabet",x);
	else
		printf("%c is not an alphabet",x);

	printf("\n");
	main();
	return 0;
}
