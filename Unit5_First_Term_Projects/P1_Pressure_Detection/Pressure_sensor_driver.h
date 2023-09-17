
#ifndef _PRESSURE_SENSOR_DRIVER_H_
#define _PRESSURE_SENSOR_DRIVER_H_


#include "state.h"

enum {
  
    PS_reading,
    PS_waiting
}PS_state_id;

//prototypes
void PS_init();
STATE_define(PS_reading);
STATE_define(PS_waiting);

//global pointer to function
void (*PS_state)();

#endif