/*
 * CA.c
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */
// define variables

#include "CA.h"

int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 50 ;

void US_set_distance(int d)
{
	CA_distance =d ;
	CA_distance <= CA_threshold ? (CA_state = STATE(CA_waiting)):(CA_state = STATE(CA_driving));
    printf("US------distance=%d------->CA\n",d);
}
STATE_define(CA_waiting)
{
	//state Name
	CA_state_id = CA_waiting ;
	printf("CA_waiting State: distance =%d Speed =%d\n",CA_distance,CA_speed);

	//state Action
	CA_speed = 0 ;
	DC_motor(CA_speed);
	//DC_Motor(CA_speed)

}

STATE_define(CA_driving)
{
	//state Name
	CA_state_id = CA_driving ;
	printf("CA_driving State: distance =%d Speed =%d\n",CA_distance,CA_speed);

	//state Action
	CA_speed = 30 ;
	DC_motor(CA_speed);

}


