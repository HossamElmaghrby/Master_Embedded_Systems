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
#include <stdbool.h>

bool is_Prime(int x)
{
	for(int i=2;i<x/2;i++)
	{
		if(x%i==0)
			return false;
	}
	return true;
}
int main(void) {

	int x,y;
	printf("Enter two number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	while(x<=y)
	{
		if(is_Prime(x))
			printf("%d ",x);

		x++;
	}
	return 0;
}
