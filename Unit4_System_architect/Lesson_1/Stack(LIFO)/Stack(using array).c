/*
 ============================================================================
 Name        : Stack(using.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Stack.h"

int main(void) {

	int Choice;
	while(1)
	{
		Dprintf("\nChosse one options:\n");
		Dprintf("1: Push\n2: Pop\n3: Peek\n4: Display\n5: Exit\n");
		scanf("%d",&Choice);

		switch(Choice)
		{
		case 1: push();
		   break;
		case 2: pop();
		   break;
		case 3: peek();
		   break;
		case 4: Display();
		   break;
		case 5: exit(0);
		default: Dprintf("invalid choice ... Try again: ");
		}
	}
	return EXIT_SUCCESS;
}
