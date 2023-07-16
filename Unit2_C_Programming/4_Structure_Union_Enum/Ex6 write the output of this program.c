/*
 ============================================================================
 Name        : Ex6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
 union job1
 {
	 char c[32];
	 float salary;
	 int worker_no;
 }u;

 struct job2
 {
	  char c[32];
	  float salary;
	  int worker_no;
 }s;
int main(void) {
	printf("size of union=%d\n",sizeof(u));
	printf("size of structure=%d",sizeof(s));
	return EXIT_SUCCESS;
}
