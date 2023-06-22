/*
 ============================================================================
 Name        : Ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int mat[10][10] ,trans[10][10];
	int r,c;
	printf("Enter the number of rows and column [2-10]: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&r,&c);

	printf("Enter the elements of matrix:\n");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("mat[%d][%d]: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&mat[i][j]);
		}
	}

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
            trans[j][i]=mat[i][j];
		}
	}

	printf("transpose of matrix:\n");
	for(int i=0;i<c;i++)
	{
		for(int j=0;j<r;j++)
		{
			printf("%d ",trans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
