
#include "state.h"
#include "pressure_sensor_driver.h"
#include "main_program.h"
#include "Alarm_monitor.h"
#include "Alarm_actuator_driver.h"
#include "test.h"

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
	PS_init();
	AA_init();

	setup();
	GPIO_INITIALIZATION();

	while(1)
	{
		PS_state =STATE(PS_reading);
		MP_state =STATE(high_pressure_detection);
		AM_state =STATE(alarm_of);
		AA_state =STATE(AA_waiting);
	    (*PS_state)();
	    (*MP_state)();
	    (*AM_state)();
	    (*AA_state)();
        
        Delay(1000);
	}
}

unsigned char Test_Case_Number = 1;
unsigned int Test_get_pressure()
{
    unsigned int Test_pressure_Input_Value = 0 ;

    switch(Test_Case_Number)
    {
    case 1:
    	printf("\n\n\n======================================\n");
    	printf("******************Integration Test************\n");
    	printf("pressure Control Project\n");
    	printf(".Eng. Hossam Elmaghrbey\n");
    	printf("\n\n\n======================================\n");

    	Test_pressure_Input_Value =12 ;
    	printf("\n\n\n======================================\n");
    	printf("Test Case 1:Input =12 Output:NOAlarm 0\n");
    	printf("Test Case 1: Running \n");
    	break ;
    }

    return Test_pressure_Input_Value ;
}

void Test_set_Alarm(int i)
{
    if(Test_Case_Number == 1 && i ==1)
    {
    	printf("Test Case 1: FAIL \n");
    	Test_Case_Number = 2 ;
    	exit(1);
    }
    else if(Test_Case_Number ==1 && i == 0)
    {
    	printf("Test Case 1: PASS \n");
    	printf("===============================");
    	Test_Case_Number =2 ;
    	exit(1);
    }

}
