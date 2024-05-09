
#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_stateFun_) void ST_##_stateFun_ ()
#define STATE(_stateFun_) ST_##_stateFun_

#include "driver.h"
//state_conection

void get_pressure_value(int p);
void high_pressure_detected();
void start_alarm();
void stop_alarm();


#endif

