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

int main(void) {
	float mat1[2][2];
	float mat2[2][2];

	printf("Enter the elements of 1th matrix:\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("arr1[%d][%d]:",i,j);
			fflush(stdin); fflush(stdout);
			scanf("%f",&mat1[i][j]);
		}
	}

	printf("Enter the elements of 2th matrix:\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("arr2[%d][%d]:",i,j);
			fflush(stdin); fflush(stdout);
			scanf("%f",&mat2[i][j]);
		}
	}

	printf("sum of matrix\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("%0.1f\t",mat1[i][j]+mat2[i][j]);
		}
		printf("\n");
	}
	return 0;
}
