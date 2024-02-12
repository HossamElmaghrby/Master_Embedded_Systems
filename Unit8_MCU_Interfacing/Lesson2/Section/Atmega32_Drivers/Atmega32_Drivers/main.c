/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "Atmega32_GPIO_Driver.h"
#include "LCD/lcd.h"
#include "Atmega32_UART_Driver.h"


int main(void)
{
	LCD_init();
    MCAL_UART_init();
	LCD_write_string("Transmit mode:");
    Cursor_pos(1,0);
    MCAL_UART_Send_Str("Hossam Bahaa");
		
	LCD_clear_screen();
	LCD_write_string("Receive mode:");
	char str[100] ;
    while (1) 
    {
	  Cursor_pos(1,0);
	  MCAL_UART_Receive_Str(str);
	  LCD_write_string(str); 	 
    }
	
}

