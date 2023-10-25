/*
 * LCD_and_keypad.c
 *
 * Created: 10/23/2023 7:38:40 AM
 * Author : elmag
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "LCD_driver/lcd.h"
#include "Keypad_driver/keypad.h"

int main(void)
{
    LCD_init();
	Keypad_init();
	
	char key_pressed ;
    while (1) 
    {
		/*LCD_write_string("Hello IN Embedded System Diploma Eng:- Hossam Elmaghraby :)");
		LCD_clear_screen();
		LCD_write_string("Numbers Examples: ");
		LCD_display_real_number(30.127);
		LCD_write_string(" ");
		LCD_display_number(12);
		_delay_ms(1000);
		LCD_clear_screen();
		_delay_ms(1000);*/
		
	
		key_pressed =Keypad_getkey();
		switch(key_pressed)
		{
			case('A') :
			 break;
			case('?') :
			LCD_clear_screen();
			break;
			default:
			LCD_write(key_pressed);
			break;
		}
    }
	return 0 ;
}

