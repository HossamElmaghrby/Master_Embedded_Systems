/*
 * Atmega32_Drivers.c
 *
 * Created: 4/25/2024 8:26:01 AM
 * Author : Elmag
 */ 

#include "Atmega32_ADC_Driver.h"
#include "LCD/lcd.h"
int main(void)
{
	ADC_Config ADC_cfg ;
	
	ADC_cfg.Auto_Trigger_enable = ADC_auto_Trigger_Disable ;
	ADC_cfg.Auto_Trigger_Source = ADC_Trigger_Source_Free_Running ;
	ADC_cfg.Channel_and_Gain =ADC_Channel_And_Gain_Single_ADC0 ;
	ADC_cfg.Data_Store = ADC_Data_Store_Right_adj ;
	ADC_cfg.Interrupt_Enable = ADC_Interrupt_Disable ;
	ADC_cfg.P_IRQ_CallBack = NULL ;
	ADC_cfg.Prescaler = ADC_Prescaler_64 ;
	ADC_cfg.Volt_Ref_Selec = ADC_Volt_Ref_Internal_AVCC ;	
	
	uint16 data =0 ;
	float volt = 0;
	uint16 Prec_Volt = 0;
    int count =0 ;
	int max_index = 0;
	int prev_index = 0 ;
	//uint16 arr[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	LCD_init() ;
	MCAL_ADC_Init(&ADC_cfg);
	Cursor_pos(0,0);
	
    while (1) 
    {
		//===========first Test ===========//
/*		
		Cursor_pos(0,0);
		LCD_write_string("ADC: ");
        data = MCAL_ADC_Read();
		Cursor_pos(1,0);
		LCD_display_number(data);
		LCD_write_string("     ");
*/
	
		
		//=========== Second Test===========//
		
/*		Cursor_pos(0,0);
		LCD_write_string("Input Volt: ");
		Cursor_pos(1,0);
		volt =((float)MCAL_ADC_Read()*5/1024);
		LCD_display_real_number(volt);
*/

        //============= Third Test============//
/*		Cursor_pos(0,0);
		LCD_write_string("percentage Volt: ");
		Prec_Volt = ((float)MCAL_ADC_Read()/1024*100);
		Cursor_pos(1,0);
		LCD_display_number(Prec_Volt);
		LCD_write_string("%   ");
*/	

       //============== Fourth Test===========//
/*	    Cursor_pos(0,0);
	    LCD_write_string("perc Volt: ");
	    Prec_Volt =((float)MCAL_ADC_Read()*100/1023);
	    LCD_display_number(Prec_Volt);
		max_index = Prec_Volt/6 ;
	    LCD_write_string("% ");
		Cursor_pos(1,0);
		if(prev_index < max_index)
		{
			count = max_index ;
            while(count--)
			{
				LCD_write(0xff);
			}
		}
		else
		{
			for(count = 15 ;count > max_index ; count--)
			{
				Cursor_pos(1,count);
				LCD_write_string(" ");
			}
		}
		prev_index = max_index ;
*/

        //===========Fifth Test===========//
		Cursor_pos(0,0);
		LCD_write_string("Temp Deg: ");
		Cursor_pos(1,0);
		volt =((float)MCAL_ADC_Read()*498.4/1024);
		LCD_display_real_number(volt);
		LCD_write_string(" C");

}
}
