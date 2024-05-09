

#ifndef _ALARM_MONITOR_H
#define _ALARM_MONITOR_H

#include "state.h"


enum
{
	alarm_of,
	alarm_on,
	waiting
}AM_state_id;

//prototypes
STATE_define(alarm_of);
STATE_define(alarm_on);
STATE_define(waiting);

void (*AM_state)();
#endif