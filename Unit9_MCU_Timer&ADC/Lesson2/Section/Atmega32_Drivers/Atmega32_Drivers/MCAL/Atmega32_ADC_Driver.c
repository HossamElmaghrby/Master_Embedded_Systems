/*
 * Atmega32_ADC_Driver.c
 *
 * Created: 4/25/2024 7:29:26 AM
 *  Author: Elmag
 */ 

#include "Atmega32_ADC_Driver.h"

ADC_Config G_ADC_Cfg ;
void MCAL_ADC_Init(ADC_Config *ADC_Cfg) 
{
	G_ADC_Cfg = *ADC_Cfg ;
	
	//Set volt reference source
	ADMUX |= ADC_Cfg->Volt_Ref_Selec ;
	
	//Set frame of data register
	ADMUX |= ADC_Cfg->Data_Store ;
	
	//Set channel of Vin
	ADMUX |= ADC_Cfg->Channel_and_Gain ;
	
	//Set trigger
	if(ADC_Cfg->Auto_Trigger_enable == ADC_auto_Trigger_Enable)
	{
		//Enable trigger
		ADCSRA |= ADC_auto_Trigger_Enable ;
		
		//Select trigger source
		SFIOR  |= ADC_Cfg->Auto_Trigger_Source ;
		
	}
	
	//Interrupt 
	if(ADC_Cfg->Interrupt_Enable == ADC_Interrupt_Enable)
	{
		Enable_Global_Interrupt();
		ADCSRA |= ADC_Cfg->Interrupt_Enable ;
	}
	
	//prescaller
	ADCSRA |=ADC_Cfg->Prescaler ;
	
	//ADCSRA .Bit 7 – ADEN: ADC Enable
	//Enable ADC
	
	ADCSRA |= (1<<7);
	
	
}
void MCAL_ADC_DeInit(void) 
{
	ADMUX  = 0x00 ;
	ADCSRA = 0x00 ;
	SFIOR  = 0x00 ;
}

uint16 MCAL_ADC_Read()
{
	ADCSRA |= ADC_Start_Conversion ;
	
	while(GET_BIT(ADCSRA , ADSC));
	
	return ADC ;
}