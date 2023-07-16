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
struct Distance
{
	int feet;
	float inch;
};

struct Distance Read_dis(int num)
{
	struct Distance dis;
	printf("Enter information of %dth distance\n"
			"Enter feet: ",num);
	fflush(stdout);
	scanf("%d",&dis.feet);
	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&dis.inch);
	return dis;

}
struct Distance add(struct Distance dis1, struct Distance dis2)
{
	struct Distance res;
	res.feet=dis1.feet+dis2.feet;
	res.inch=dis1.inch+dis2.inch;

	if(res.inch>=12.0)
	{
		res.inch-=12.0;
		res.feet++;
	}
	return res;
}
int main(void) {
	struct Distance dis1,dis2,res;
	dis1=Read_dis(1);
	dis2=Read_dis(2);
	res=add(dis1,dis2);
	printf("sum of distance=%d\'-%0.1f\"",res.feet,res.inch);
	return EXIT_SUCCESS;
}
