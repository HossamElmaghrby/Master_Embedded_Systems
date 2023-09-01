/*
 * US.h
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */

#ifndef US_H_
#define US_H_

#include "state.h"
//Define States
enum{
	US_busy,

}US_state_id;

//declare state function US
STATE_define(US_busy);
void US_init();
void (*US_state)();


#endif /* US_H_ */
