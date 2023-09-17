

#ifndef _MAIN_PROGRAM_H_
#define _MAIN_PROGRAM_H_

#include "state.h"

enum
{
	high_pressure_detection
}MP_state_id;
//prototypes
STATE_define(high_pressure_detection);

//global pointer to function

void (*MP_state)();

#endif