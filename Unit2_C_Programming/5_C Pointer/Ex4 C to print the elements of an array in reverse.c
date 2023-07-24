/*
 ============================================================================
 Name        : Ex4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int arr[15],size;
	int *ptr=arr;
	printf("Enter the size of the Array[MAX 15]: ");
	fflush(stdout);
	scanf("%d",&size);

	int count=0;
	while(count++<size)
	{
	  printf("Enter %dth element: ",count);
	  fflush(stdout);
	  scanf("%d",ptr);
	  ptr++;
	}
	ptr--;
	while(--count)
	{
		printf("Enter %dth element=%d\n",count,*ptr);
		ptr--;
	}
	return EXIT_SUCCESS;
}
