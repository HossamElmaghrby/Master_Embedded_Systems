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
	int arr[20];
	int size,insNum,loc;
	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);
	printf("Enter elements: ");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<size;i++)
		scanf("%d",&arr[i]);

	printf("Enter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
     scanf("%d",&insNum);

     printf("Enter the location: ");
 	fflush(stdin); fflush(stdout);
    scanf("%d",&loc);

    for(int i=size;i>=loc;i--)
    {
       arr[i]=arr[i-1];
    }
    size++;
    arr[loc-1]=insNum;
    printf("the new array is: ");
    for(int i=0;i<size;i++)
    {
    	printf("%d ",arr[i]);
    }

	return 0;
}
