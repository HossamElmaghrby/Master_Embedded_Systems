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

struct Sstudent
{
	char name[50];
	int roll;
	float marks;
}s;

void Read_Std()
{
	printf("Enter the information of student\nname:");
	fflush(stdout);
	scanf("%s",s.name);
	printf("Roll:");
	fflush(stdout);
	scanf("%d",&s.roll);
	printf("Marks:");
	fflush(stdout);
	scanf("%f",&s.marks);


}
void Print_Std( )
{
	printf("\nDisplaying Information\n"
	       "Name: %s\n"
		   "Roll: %d\n"
		   "Marks: %0.2f\n",s.name,s.roll,s.marks);
	fflush(stdout);
}
int main(void) {

	Read_Std();
	Print_Std();
}
