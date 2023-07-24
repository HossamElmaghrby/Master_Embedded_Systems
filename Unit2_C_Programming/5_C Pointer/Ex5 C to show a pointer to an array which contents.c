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

struct employee
{
	char *empname;
	int empid;

};
int main(void) {

	struct employee emp1={"hossam",2003},emp2={"mohamed",1095};
	struct employee *arr[2]={&emp1,&emp2};
	struct employee (*(*pt)[2])=&arr;

	printf("Employee name: %s\n",(*(*pt+1))->empname);
	printf("Employee id: %d",(*(*pt+1))->empid);

	return EXIT_SUCCESS;
}
