/*
 * lcd.h
 *
 * Created: 10/23/2023 7:42:37 AM
 *  Author: elmag
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Atmega32_Device_Header.h"
#include "Atmega32_GPIO_Driver.h"
#define LCD_DATA_PORT GPIOA
#define LCD_CONTROL_PORT GPIOB


#define RS GPIO_PIN_1
#define RW GPIO_PIN_2
#define EN GPIO_PIN_3

#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

void LCD_init(void);
void LCD_Command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_busy(void);
void LCD_Kick(void);
void LCD_clear_screen(void);
void Cursor_pos(unsigned char X_pos , unsigned char Y_pos);
void LCD_write(unsigned char data);
void LCD_write_string(char *data);
void LCD_display_number(int number);
void LCD_display_real_number(double number);
#endif /* LCD_H_ */