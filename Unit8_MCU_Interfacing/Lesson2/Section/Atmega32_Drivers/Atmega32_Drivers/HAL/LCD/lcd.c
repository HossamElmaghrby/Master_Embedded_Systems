/*
 * lcd.c
 *
 * Created: 10/23/2023 7:43:00 AM
 *  Author: Elmag
 */ 
#include "LCD/lcd.h"
#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE

GPIO_PinConfig_t pincfg ;
void LCD_init(void)
{
	_delay_ms(20);
	//configuration RS pin
	pincfg.GPIO_PinNumber = RS ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init( LCD_CONTROL_PORT , &pincfg);
	
	//configuration RW pin
	pincfg.GPIO_PinNumber = RW ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init( LCD_CONTROL_PORT , &pincfg);
		
	//configuration EN pin
	pincfg.GPIO_PinNumber = EN ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init( LCD_CONTROL_PORT , &pincfg);
	
	//LCD_DataDir_PORT =0xf ;
	//configuration LCD_DATA_PORT pins
	pincfg.GPIO_PinNumber =GPIO_PIN_4 ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init(LCD_DATA_PORT ,&pincfg);
	
	pincfg.GPIO_PinNumber =GPIO_PIN_5 ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init(LCD_DATA_PORT ,&pincfg);
	
	pincfg.GPIO_PinNumber =GPIO_PIN_6 ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init(LCD_DATA_PORT ,&pincfg);	

	pincfg.GPIO_PinNumber =GPIO_PIN_7 ;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	MCAL_GPIO_Init(LCD_DATA_PORT ,&pincfg);	
	
	//LCD_ContDir_PORT |=((1<<RS) | (1<<RW) |(1<<EN));
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT , EN ,GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS ,GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW ,GPIO_PIN_RESET);
	
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
	LCD_Command(LCD_DISP_ON_CURSOR);
}

void LCD_Command(unsigned char command)
{
	   #ifdef EIGHT_BIT_MODE
	   
	   LCD_busy();
	  // LCD_DATA_PORT =command ;       // Data lines are set to send data
	  MCAL_GPIO_WritePort(LCD_DATA_PORT , command);
	  
	  //LCD_Cont_PORT &=~(1<<RS);      // RS set 0 to command
	  MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS ,GPIO_PIN_RESET);
	  
	  //LCD_Cont_PORT &=~(1<<RW);      // RW set 0 to write
	   MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW ,GPIO_PIN_RESET);
	   
       LCD_Kick();
       #endif
      
	  #ifdef FOUR_BIT_MODE
		LCD_busy();
		//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		MCAL_GPIO_WritePort(LCD_DATA_PORT , 0x0F) ;
		MCAL_GPIO_WritePort(LCD_DATA_PORT , (command & 0xF0)) ;
		
		//LCD_Cont_PORT &= ~ ((1<<RW)|(1<<RS));
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW ,GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS ,GPIO_PIN_RESET);
		
		LCD_Kick();
		
		//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command << 4);
		MCAL_GPIO_WritePort(LCD_DATA_PORT , 0x0F) ;
		MCAL_GPIO_WritePort(LCD_DATA_PORT , (command <<4)) ;
		
		//LCD_CONTROL_PORT &= ~ ((1<<RW)|(1<<RS));
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW ,GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS ,GPIO_PIN_RESET);
		LCD_Kick();
      #endif
	  
}

void LCD_write(unsigned char data)
{
	 #ifdef EIGHT_BIT_MODE
	    LCD_busy();
	  	//LCD_DATA_PORT =data ;
		 MCAL_GPIO_WritePort(LCD_DATA_PORT , data) ;
	    //LCD_Cont_PORT |=(1<<RS);
	     MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS,GPIO_PIN_SET) ; 
	  	//LCD_Cont_PORT &= ~(1<<RW);
	  	 MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW,GPIO_PIN_RESET) ; 
	  	LCD_Kick();
     #endif
 	
	 #ifdef FOUR_BIT_MODE
	 	    //LCD_DATA_PORT =(LCD_DATA_PORT & 0x0F) |(data & 0xF0) ;
			MCAL_GPIO_WritePort(LCD_DATA_PORT , 0x0F) ;
			MCAL_GPIO_WritePort(LCD_DATA_PORT , (data & 0xF0)) ;
			
	 	    MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS,GPIO_PIN_SET) ;
	 	    MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW,GPIO_PIN_RESET) ;
			 
		    LCD_Kick();
			
	      	//LCD_DATA_PORT =(LCD_DATA_PORT & 0x0F) |(data << 4) ;
			MCAL_GPIO_WritePort(LCD_DATA_PORT , 0x0F) ;
			MCAL_GPIO_WritePort(LCD_DATA_PORT , (data<<4)) ;
			//LCD_Cont_PORT |=(1<<RS);
		    MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS,GPIO_PIN_SET) ; 	    
			//LCD_Cont_PORT &= ~(1<<RW);
			MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW,GPIO_PIN_RESET) ;
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
	//LCD_DataDir_PORT =0x0;
		pincfg.GPIO_PinNumber = GPIO_PIN_4;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA_PORT, &pincfg);

		pincfg.GPIO_PinNumber = GPIO_PIN_5;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA_PORT, &pincfg);

		pincfg.GPIO_PinNumber = GPIO_PIN_6;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA_PORT, &pincfg);

		pincfg.GPIO_PinNumber = GPIO_PIN_7;
		pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_DATA_PORT, &pincfg);
		
		//LCD_Cont_PORT |=(1<<RW); //Read
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RW,GPIO_PIN_SET) ;
		//LCD_Cont_PORT &=~(1<<RS); // command
		MCAL_GPIO_WritePin(LCD_CONTROL_PORT , RS,GPIO_PIN_RESET) ;
		
   		LCD_Kick();
		   
		//LCD_DataDir_PORT =0xF ;
		pincfg.GPIO_PinNumber = GPIO_PIN_4 ;
		pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
		MCAL_GPIO_Init(LCD_DATA_PORT , &pincfg);
	
		pincfg.GPIO_PinNumber = GPIO_PIN_5;
		pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
		MCAL_GPIO_Init(LCD_DATA_PORT , &pincfg);
	
		pincfg.GPIO_PinNumber = GPIO_PIN_6;
		pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
		MCAL_GPIO_Init(LCD_DATA_PORT , &pincfg);

		pincfg.GPIO_PinNumber = GPIO_PIN_7;
		pincfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
		MCAL_GPIO_Init(LCD_DATA_PORT , &pincfg);		
		//LCD_Cont_PORT &=~(1<<RW);
	    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW, GPIO_PIN_RESET);
	    	
}
void LCD_Kick()
{
	//LCD_Cont_PORT &=~(1<<EN);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT , EN ,GPIO_PIN_RESET);
	_delay_ms(250);
	//LCD_Cont_PORT |=(1<<EN);
	MCAL_GPIO_WritePin(LCD_CONTROL_PORT , EN ,GPIO_PIN_SET);
}

void LCD_clear_screen()
{
	LCD_Command(LCD_CLEAR_SCREEN);
}

void Cursor_pos(unsigned char X_pos , unsigned char Y_pos)
{
	unsigned char address =0;
	if(X_pos == 0)
	address =LCD_BEGIN_AT_FIRST_ROW ;
	else if(X_pos == 1)
	address = LCD_BEGIN_AT_SECOND_ROW;
	
	if(Y_pos>=0 && Y_pos<16)
	address+=Y_pos;
	
	LCD_Command(address);
}

