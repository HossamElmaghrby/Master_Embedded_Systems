/*
 * lcd.c
 *
 * Created: 10/23/2023 7:43:00 AM
 *  Author: elmag
 */ 
#include "lcd.h"

#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE
void LCD_init(void)
{
	_delay_ms(20);
	LCD_ContDir_PORT |=((1<<RS) | (1<<RW) |(1<<EN));
	LCD_DataDir_PORT =0xff ;
	_delay_ms(15);
	
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	LCD_Command(LCD_FUNCTION_8BIT_2LINES); 
    #endif
	
	#ifdef FOUR_BIT_MODE
	LCD_Command(0x02);
	LCD_Command(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_Command(LCD_ENTRY_MODE);
	LCD_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Command(LCD_DISP_ON_CURSOR_BLINK);
	
}

void LCD_Command(unsigned char command)
{
	   #ifdef EIGHT_BIT_MODE
	   
	   LCD_busy();
	   LCD_DATA_PORT =command ;       // Data lines are set to send data
	   LCD_Cont_PORT &=~(1<<RS);  // RS set 0 to command
	   LCD_Cont_PORT &=~(1<<RW);  // RW set 0 to write
       LCD_Kick();
       #endif
      
	  #ifdef FOUR_BIT_MODE
		LCD_busy();
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		LCD_Cont_PORT &= ~ ((1<<RW)|(1<<RS));
		LCD_Kick();
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command << 4);
		LCD_Cont_PORT &= ~ ((1<<RW)|(1<<RS));
		LCD_Kick();
      #endif
	  
}

void LCD_write(unsigned char data)
{
	 #ifdef EIGHT_BIT_MODE
	    LCD_busy();
	  	LCD_DATA_PORT =data ;
	  	LCD_Cont_PORT |=(1<<RS);
	  	LCD_Cont_PORT &= ~(1<<RW);
	  	
	  	LCD_Kick();
     #endif
 	
	 #ifdef FOUR_BIT_MODE
	 	    LCD_DATA_PORT =(LCD_DATA_PORT & 0x0F) |(data & 0xF0) ;
	 	    LCD_Cont_PORT |=(1<<RS);
	 	    LCD_Cont_PORT &= ~(1<<RW);
		    LCD_Kick();
	      	LCD_DATA_PORT =(LCD_DATA_PORT & 0x0F) |(data << 4) ;
			LCD_Cont_PORT |=(1<<RS);
			LCD_Cont_PORT &= ~(1<<RW);
	 	    LCD_Kick();
     #endif
}

void LCD_write_string(char *string)
{
	int count =0;
	while(*string >0)
	{
		count++ ;
		LCD_write(*string++);
		if(count == 16)
		{
			Cursor_pos(1,0);
		}
		else if(count ==32 || count ==33)
		{
				LCD_clear_screen();
				Cursor_pos(0,0);
				count =0;
		}
	}
}

void LCD_busy()
{
	LCD_DataDir_PORT =0x00 ;
	LCD_Cont_PORT |=(1<<RW); //Read
	LCD_Cont_PORT &=~(1<<RS); // command
	LCD_Kick();
	LCD_DataDir_PORT =0xFF ;
	LCD_Cont_PORT &=~(1<<RW);
}
void LCD_Kick()
{
	LCD_Cont_PORT &=~(1<<EN);
	_delay_ms(50);
	LCD_Cont_PORT |=(1<<EN);

}

void LCD_clear_screen()
{
	LCD_Command(LCD_CLEAR_SCREEN);
}

void Cursor_pos(unsigned char X_pos , unsigned char Y_pos)
{
	unsigned char address =0;
	if(X_pos == 0)
	address =0x80 ;
	else if(X_pos == 1)
	address = 0xC0;
	
	if(Y_pos>=0 && Y_pos<16)
	address+=Y_pos;
	
	LCD_Command(address);
}
void LCD_display_number(int number)
{
	char str[5];
	
	itoa(number , str ,10);
	LCD_write_string(str);
}
void LCD_display_real_number(double number)
{
	char str[10];
	
	char tmpSign  = (number < 0)? '-': ' ' ;
	float tmpVal   =(number < 0)? -number : number ;
	
	int tmpInt1 =tmpVal ;
	float tmpFrac =tmpVal - tmpInt1 ;
	int tmpInt2 =tmpFrac*10000 ;
	
	sprintf(str, "%s%d.%04d" ,tmpSign ,tmpInt1 ,tmpInt2);
	
	LCD_write_string(str);
	
}