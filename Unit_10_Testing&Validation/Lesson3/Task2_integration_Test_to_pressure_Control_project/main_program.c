
#include "main_program.h"

//modules variables
int pressure_value =0 ;
int pressure_threshold =20 ;

void get_pressure_value(int P)
{
	pressure_value = P ;

   if(pressure_value > pressure_threshold )
    {
		high_pressure_detected();
    } 

   	MP_state=STATE(high_pressure_detection);
}

STATE_define(high_pressure_detection)
{
	MP_state_id = high_pressure_detection;

	MP_state=STATE(high_pressure_detection);
}
