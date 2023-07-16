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

struct Sstudent
{
	char name[50];
	int roll;
	float marks;
}s[10];

void Read_Std(int index)
{
	printf("for roll number %d\n",index+1);
	fflush(stdout);
	printf("Enter name: ");
	fflush(stdout);
	scanf("%s",s[index].name);
    s[index].roll=index+1;
	printf("Marks:");
	fflush(stdout);
	scanf("%f",&s[index].marks);


}
void Print_Std(int index)
{
	printf("\nDisplaying Information\n"
	       "Name: %s\n"
		   "Roll: %d\n"
		   "Marks: %0.2f\n",s[index].name,s[index].roll,s[index].marks);
	fflush(stdout);
}
int main(void) {

	printf("Enter information of students:\n");
	for(int i=0;i<10;i++)
		Read_Std(i);

   for(int i=0;i<10;i++)
   {
	   	   Print_Std(i);
   }

   return 0;
}
