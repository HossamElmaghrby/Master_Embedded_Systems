/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "Atmega32_GPIO_Driver.h"
#include "LCD/lcd.h"
#include "Atmega32_UART_Driver.h"
#include "avr/interrupt.h"
int main(void)
{
	LCD_init();
	UART_config UART_CFG ;
	UART_CFG.BaudRate  = UART_BaudRate_9600 ;
	UART_CFG.data_size = UART_data_Size_8B ;
	UART_CFG.IRQ_Enable= UART_Interrupt_Enable_NONE ;
	UART_CFG.P_IRQ_CallBack = NULL ;
	UART_CFG.parity =UART_Parity_NONE ;
	UART_CFG.Speed_Mode = UART_Speed_Mode_Normal ;
	UART_CFG.StopBit = UART_StopBits_1 ;
	UART_CFG.USART_Mode = UART_Mode_TX_AND_RX ; 
    MCAL_UART_init(UART1 , &UART_CFG);
	
	
	LCD_write_string("Transmit mode:");
	MCAL_UART_Send_Str("Hossam Bahaa");
    Cursor_pos(1,0);
	
	// sei();
     //MCAL_UART_SendString_Asynch("Hossam");
	
	LCD_clear_screen();
	LCD_write_string("Receive mode:");
	LCD_clear_screen();	
	
	uint8 str[100] ,data ;
	uint8 x =0;
    while (1) 
    {

/*======================================*/
/*         Receive char with block      */
/*======================================*/
	  /*Cursor_pos(1,0);
	  data= MCAL_UART_Receive();
	  LCD_write(data); */	
	  
	  	
/*======================================*/
/*       Receive string with block      */
/*======================================*/
	   /*Cursor_pos(1,0);
	   MCAL_UART_Receive_Str(str);
	   LCD_write_string(str); */

/*======================================*/
/*       Receive char with No block      */
/*======================================*/
	  Cursor_pos(1,0);
	  MCAL_UART_Receive_perodicCheck(&data);
	  LCD_write(data);
	  
	  	  
	  //=======counter==========//
	  Cursor_pos(0,0);
	  if(x==9)
		  x= 0;	
	  x++;	
	  LCD_display_number(x); 
	 _delay_ms(200);
		  
	}
}
