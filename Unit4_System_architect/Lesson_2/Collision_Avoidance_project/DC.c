/*
 * DC.c
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */
// define variables

#include "DC.h"

int DC_speed = 0 ;

void DC_motor(int s)
{

	DC_speed = s;
	DC_state =STATE(DC_busy);
	printf("CA-----speed = %d----->DC \n",DC_speed);
}

STATE_define(DC_idle)
{
	//state Name
	DC_state_id = DC_idle ;

	printf("DC_idle State: Speed =%d\n",DC_speed);
}

STATE_define(DC_busy)
{
	//state Name
	DC_state_id = DC_busy ;

    DC_state =STATE(DC_idle);
	printf("DC_busy State: distance =%d Speed =%d\n",DC_speed);
}

