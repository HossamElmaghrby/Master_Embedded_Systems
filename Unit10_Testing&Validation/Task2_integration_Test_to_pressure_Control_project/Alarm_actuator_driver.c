

#include "Alarm_actuator_driver.h"

void AA_init(){

	//init alarm actuator 
	//call the alarm actuator driver
}


void start_alarm()
{
   Set_Alarm_actuator(0);

   STATE(AA_waiting);
}
void stop_alarm()
{
   Set_Alarm_actuator(1);

   STATE(AA_waiting);

}
STATE_define(AA_waiting)
{
   AA_state_id = AA_waiting ;
}
