

#include "pressure_sensor_driver.h"

//Module variables
int Pressure_Value = 0;
int pressure_sensor_pull_time = 10 ;

void PS_init()
{
	//init Pressure Sensor
	//call the Pressure sensor Driver 
}


STATE_define(PS_reading)
{
	//state action
	PS_state_id = PS_reading ;
	//read from the Pressure sensor
    Pressure_Value = getPressureVal();

    get_pressure_value(Pressure_Value);

     PS_state = STATE(PS_waiting);
}

STATE_define(PS_waiting)
{
	//state action
    PS_state_id = PS_waiting ;
    //timer 
    Delay(pressure_sensor_pull_time);
    PS_state=STATE(PS_reading);
}