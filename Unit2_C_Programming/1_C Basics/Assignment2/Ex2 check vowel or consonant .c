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
#include <ctype.h>
int main(void) {
	char x='a';
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);

	if(x=='a'||x=='e'||x=='i'||x=='o'||x=='u')
		printf("%c is a vowel",x);
	else if(isalpha(x))
		printf("%c is a consonant",x);
	else
		printf("%c is not alphabet",x);
	printf("\n");
    main();
	return 0;
}
