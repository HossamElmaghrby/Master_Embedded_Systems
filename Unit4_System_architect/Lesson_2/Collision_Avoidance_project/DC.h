/*
 * DC.h
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

//Define States
enum{
	DC_idle,
	DC_busy
}DC_state_id;


//declare state function DC
STATE_define(DC_idle);
STATE_define(DC_busy);
void DC_init();
void (*DC_state)();


#endif /* DC_H_ */
