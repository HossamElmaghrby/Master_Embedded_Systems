
#include "state.h"
#include "pressure_sensor_driver.h"
#include "main_program.h"
#include "Alarm_monitor.h"
#include "Alarm_actuator_driver.h"

void setup()
{
   	//init all the drivers
	//init IRQ .....
	//init HAL US_Driver DC_Driver
	//init Block
	//set STates pointer for each block 

	PS_state =STATE(PS_reading);
	MP_state =STATE(high_pressure_detection);
	AM_state =STATE(alarm_of);
	AA_state =STATE(AA_waiting);
}

void main()
{
	setup();
	GPIO_INITIALIZATION();

	while(1)
	{
	    PS_state();
	    MP_state();
	    AM_state();
	    AA_state();
	}
}
