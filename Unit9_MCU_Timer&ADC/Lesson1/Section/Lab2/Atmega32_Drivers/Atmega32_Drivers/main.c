/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "Atmega32_Timer0_Driver.h"
uint16_t Timer_counter = 0;
void Timer0_Compare_Match_interrup_Handler()
{
	Timer_counter++ ;
	
	if(Timer_counter == 10000)
	{
		//Toggle_led every one second
		TOGGLE_BIT(PORTC , 0);
		
		//clear counter
		Timer_counter = 0 ;
	}
}

int main(void)
{
    DDRB = 0xFF ;
	
    //Configure timer0
	Timer0_Config Timer0_Config ;
	
	Timer0_Config.Timer0_Mode = Timer0_Mode_Fast_PWM ;
	Timer0_Config.Clock_Select = Timer0_Clock_Internal_Prescaler_8 ;
	Timer0_Config.IRQ_Enable = Timer0_IRQ_Compare_Match_Enable ;
	Timer0_Config.Output_Compare =Timer0_OC_Set ;
	Timer0_Config.P_IRQ_CallBack = NULL ;
	
	
	// initialization Timer0
	MCAL_Timer0_Init(&Timer0_Config);
		
    while (1) 
    {
			//Set compare Value
			MCAL_Timer0_Set_Compare_Value(255);
			
			_delay_ms(5000);
			
			MCAL_Timer0_Set_Compare_Value(200);
			
			_delay_ms(15000);
			
			MCAL_Timer0_Set_Compare_Value(100);

			_delay_ms(15000);
			
			MCAL_Timer0_Set_Compare_Value(0);
			
			_delay_ms(15000);
	}
}
