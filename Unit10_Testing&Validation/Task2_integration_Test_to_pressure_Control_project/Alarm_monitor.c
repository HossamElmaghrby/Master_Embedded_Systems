

#include "Alarm_monitor.h"
//modules variables
int alarm_time = 60 ;

 void high_pressure_detected()
 {
    AM_state = STATE(alarm_on);
 }

STATE_define(alarm_of)
{
    AM_state_id = alarm_of ;

     stop_alarm();

}
STATE_define(alarm_on)
{
    AM_state_id = alarm_on ;

    start_alarm();

    AM_state = STATE(waiting);
}
STATE_define(waiting)
{
    Delay(alarm_time);

    AM_state = STATE(waiting);

    stop_alarm();

    AM_state = STATE(alarm_of);
}