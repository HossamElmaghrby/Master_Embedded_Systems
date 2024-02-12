/*
 * Atmega32_UART_Driver.c
 *
 * Created: 1/31/2024 1:33:05 PM
 *  Author: Elmag
 */ 

#include "Atmega32_UART_Driver.h"
#include "LCD/lcd.h"
void MCAL_UART_init(void)

{
	//CLR_BIT(UCSRC , UMSEL);
	//Baud Rate
	UBRRL =51;
	CLR_BIT(UCSRA , U2X);          // (default)
	//Frame
	 //parity mode (NO Parity)
	CLR_BIT(UCSRC , UPM0);        // (default)
	CLR_BIT(UCSRC , UPM1);        // (default)
	 // Character Size (8-bit size)
	SET_BIT(UCSRC , UCSZ0);       // (default)
	SET_BIT(UCSRC , UCSZ1);       // (default)
	CLR_BIT(UCSRB , UCSZ2);       // (default)
	CLR_BIT(UCSRB , UCSZ2);       // (default)
      	 
	//Enable
	SET_BIT(UCSRB , RXEN);
	SET_BIT(UCSRB , TXEN);
	
	// UCPOL: Clock Polarity
	//This bit is used for Synchronous mode only.
	// Write this bit to zero when Asynchronous mode is used
	CLR_BIT(UCSRC , UCPOL);       // (default)
}
void MCAL_UART_Send(uint8_t data)
{
	while(!GET_BIT(UCSRA , UDRE));
	UDR = data ;
}
uint8_t MCAL_UART_Receive(void) 
{
	while(!(GET_BIT(UCSRA,RXC)));
	return UDR ; 
}

void  MCAL_UART_SndNumberU32(uint32 NUM)
{
	uint8 *p =&NUM ;
	
	MCAL_UART_Send(p[0]); 
    MCAL_UART_Send(p[1]);
	MCAL_UART_Send(p[2]);
	MCAL_UART_Send(p[3]);
}
uint32 MCAL_UART_ReceiveNumberU32(void)
{
	uint32 num;
	uint8 *p = & num;
	
	p[0]=MCAL_UART_Receive();
	p[1]=MCAL_UART_Receive();
    p[2]=MCAL_UART_Receive();
	p[3]=MCAL_UART_Receive();
	
	return num ;
}

void MCAL_UART_Send_Str(char *str)
{
	uint8 i =0;
	while(str[i] > 0)
	{
		MCAL_UART_Send(str[i]);
		i++;
	}
	MCAL_UART_Send('\r');
}
void MCAL_UART_Receive_Str(char *str)
{
	uint8 i =0 ;
	str[i] = MCAL_UART_Receive();
	while(str[i]  != '\r')
	{
		 i++ ;	 
		 str[i]= MCAL_UART_Receive(); 
	}
	str[i]='\0';
}