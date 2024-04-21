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
    DDRC = 0xFF ;
	CLR_BIT(PORTC , 0);
	
    //Configure timer0
	Timer0_Config Timer0_Config ;
	
	Timer0_Config.Timer0_Mode = Timer0_Mode_CTC ;
	Timer0_Config.Clock_Select = Timer0_Clock_Internal_Prescaler_8 ;
	Timer0_Config.IRQ_Enable = Timer0_IRQ_Compare_Match_Enable ;
	Timer0_Config.Output_Compare =Timer0_Clock_Stop ;
	Timer0_Config.P_IRQ_CallBack = Timer0_Compare_Match_interrup_Handler ;
	
	//Set compare Value
	MCAL_Timer0_Set_Compare_Value(100);
	
	// initialization Timer0
	MCAL_Timer0_Init(&Timer0_Config);
    while (1) 
    {
		
	}
}
