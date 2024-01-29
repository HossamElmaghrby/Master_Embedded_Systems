/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "Atmega32_GPIO_Driver.h"
#include "LCD/lcd.h"


int main(void)
{
	LCD_init();
	LCD_write_string("Hossam Elmaghrby");
    while (1) 
    {
	   
    }
}

