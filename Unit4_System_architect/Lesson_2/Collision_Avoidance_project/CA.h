/*
 * CA.h
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
#include <stdio.h>
#include <stdlib.h>
//Define States
enum{
	CA_waiting,
	CA_driving
}CA_state_id;


//declare state function CA
STATE_define(CA_waiting);
STATE_define(CA_driving);

void (*CA_state)();


#endif /* CA_H_ */
