/*
 ============================================================================
 Name        : Ex7.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x=0;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	if(x < 0)
		printf("Error!!! factorial of negative number does't exist");
	else
	{
		int j=1;
		for(int i=1;i <= x;++i)
			j*=i;
		printf("factorial = %d",j);
	}
	printf("\n");
	main();
	return 0;
}
