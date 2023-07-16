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
struct complex
{
	float real;
	float image;
};
struct complex Read_complex(int num)
{
	struct complex c;
	printf("for %dth complex number"
			"\nEnter real and imaginary respectively:",num);
	fflush(stdout);
	scanf("%f %f",&c.real,&c.image);
	return c;

}
struct complex add(struct complex c1, struct complex c2)
{
   struct complex res;
    res.real=c1.real+c2.real;
    res.image=c1.image+c2.image;
    return res;
}

int main(void) {

	struct complex c1,c2,res;
	c1=Read_complex(1);
	c2=Read_complex(2);
	res=add(c1,c2);
	printf("sum=%0.1f+%0.1fi",res.real,res.image);
	return EXIT_SUCCESS;
}
