/*
 * US.c
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */
// define variables

#include "US.h"

int US_distance = 0 ;

int US_Get_distance_random (int min ,int max,int count ) ;

STATE_define(US_busy)
{
	//state Name
	US_state_id = US_busy ;

	//state Action

	US_distance =US_Get_distance_random (45 ,55, 1);
	printf("US_busy State: distance =%d \n",US_distance);

	US_set_distance(US_distance);
	US_state = STATE(US_busy);
}

int US_Get_distance_random (int min ,int max,int count )
{
	// this will generate random number in range minimum and max
   int i;
   for(i=0; i < count ; i++ )
   {
	   int rand_num=(rand() % (max - min + 1)) + min ;
	   return rand_num ;
   }
}
