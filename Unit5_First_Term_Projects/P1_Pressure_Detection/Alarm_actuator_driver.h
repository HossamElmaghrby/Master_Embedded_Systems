
#ifndef _ALARM_ACTUATOR_DRIVER_H_
#define _ALARM_ACTUATOR_DRIVER_H_

#include "state.h"

enum 
{
	AA_waiting
}AA_state_id;

void AA_init();
STATE_define(AA_waiting);

void (*AA_state)();
#endif