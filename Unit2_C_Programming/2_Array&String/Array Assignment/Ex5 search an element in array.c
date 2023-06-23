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

	int size,searEle;
	int arr[100];

	printf("Enter the number of elements[2-100]:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);
	printf("Enter elements: ");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
	}
	printf("Enter the element to be searched: ");
	fflush(stdin); fflush(stdout);
    scanf("%d",&searEle);

    for(int i=0;i<size;i++)
    {
    	if(arr[i]==searEle)
    	{
    		printf("Number found at location =%d",i+1);
    		return 0;
    	}
    }
    printf("The number not found");
	return 0;
}
