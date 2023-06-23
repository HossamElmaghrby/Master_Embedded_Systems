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

int main(void) {
	int x;
	float sum=0,avg;
	float arr[100];

	printf("Enter the number of data[2-100]:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	for(int i=0;i<x;i++)
	{
		printf("Enter %dth: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&arr[i]);
	}

	for(int i=0;i<x;i++)
		sum+=arr[i];
	avg=sum/x;
	printf("Average= %0.2f",avg);
	return 0;
}
