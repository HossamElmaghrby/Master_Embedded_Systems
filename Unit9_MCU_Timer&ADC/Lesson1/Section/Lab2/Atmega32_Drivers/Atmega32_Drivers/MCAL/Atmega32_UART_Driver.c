/*
 * Atmega32_UART_Driver.c
 *
 * Created: 1/31/2024 1:33:05 PM
 *  Author: Elmag
 */ 

#include "Atmega32_UART_Driver.h"
#include "LCD/lcd.h"


static uint8 *TX_str ;
static uint8 flag_send =1;

UART_config *Global_UART_cfg = NULL ;
void MCAL_UART_init(UART_TypeDef_t* UARTx , UART_config* UART_cfg)
{
	
	Global_UART_cfg =UART_cfg ;
	//specify the speed mode normal or double
	UARTx->_UCSRA = UART_cfg->Speed_Mode  ;
	//Baud Rate
	 if(UART_cfg->Speed_Mode == UART_Speed_Mode_Normal)
	 {
		 UARTx->_UBRRL = BAUD(F_CPU ,UART_cfg->BaudRate ,16);
		 
	 }
	 else
	 {
		 UARTx->_UBRRL = BAUD(F_CPU , UART_cfg->BaudRate ,8);
	 }
	//Frame
	
	 //parity mode (NO Parity)
	 UARTx->RC_RH._UCSRC |=UART_cfg->parity ;
	 
	 // Character Size (8-bit size)
	 if(UART_cfg->data_size == UART_data_Size_5B)
	 {
		 UARTx->RC_RH._UCSRC &=~(1<<1);
		 UARTx->RC_RH._UCSRC &=~(1<<2);
		 UARTx->_UCSRB &=~(1<<2);
	 }
	 else if(UART_cfg->data_size == UART_data_Size_6B)
	 {
		 UARTx->RC_RH._UCSRC |=(1<<1);
		 UARTx->RC_RH._UCSRC &=~(1<<2);
		 UARTx->_UCSRB &=~(1<<2);
	 }
	 else if(UART_cfg->data_size == UART_data_Size_7B)
	 {
		 	 UARTx->RC_RH._UCSRC &=~(1<<1);
		 	 UARTx->RC_RH._UCSRC |=(1<<2);
		 	 UARTx->_UCSRB &=~(1<<2);
	 }
	 else if(UART_cfg->data_size == UART_data_Size_8B)
	 {
		 UARTx->RC_RH._UCSRC |=(1<<1);
		 UARTx->RC_RH._UCSRC |=(1<<2);
		 UARTx->_UCSRB &=~(1<<2);
	 }	
	 else if(UART_cfg->data_size == UART_data_Size_9B)
	 {
		 UARTx->RC_RH._UCSRC |=(1<<1);
		 UARTx->RC_RH._UCSRC |=(1<<2);
		 UARTx->_UCSRB |=(1<<2);
	 }	 
	 
	 UARTx->RC_RH._UCSRC|=UART_cfg->StopBit ; 
	  
	//interrupt enable
	
	if(UART_cfg->IRQ_Enable != UART_Interrupt_Enable_NONE)
	{
		Enable_Global_Interrupt();
		UARTx->_UCSRB |= UART_cfg->IRQ_Enable ; 
	}    	 
	//Enable
	UARTx->_UCSRB |= UART_cfg->USART_Mode ;
    
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
	uint8 *p = &num;
	
	p[0]=MCAL_UART_Receive();
	p[1]=MCAL_UART_Receive();
    p[2]=MCAL_UART_Receive();
	p[3]=MCAL_UART_Receive();
	
	return num ;
}

void MCAL_UART_Send_Str(uint8 *str)
{
	uint8 i =0;
	while(str[i] > 0)
	{
		MCAL_UART_Send(str[i]);
		i++;
	}
	MCAL_UART_Send('\r');
}
void MCAL_UART_Receive_Str(uint8 *str)
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

uint8 MCAL_UART_Receive_perodicCheck( uint8 *data)
{
	if(GET_BIT(UCSRA , RXC))
	{
		*data = UDR ;
		return 1;
	}
	return 0;
}

void MCAL_UART_SendNoBlock(uint8 data)
{
	UDR = data ;
}
uint8 MCAL_UART_ReceiveNoBlock(void)
{
	return UDR ;
}

void MCAL_UART_SendString_Asynch(uint8 * str)
{
 	if(flag_send ==1)
	 {
		 
		 UART_Interrupt_Enable_TXCIE;
		 TX_str =str ;
		 MCAL_UART_SendNoBlock(str[0]);
		 flag_send = 0;
	 }
}

ISR(USART_TXC_vect)
{
	static uint8 i= 1;
	if(TX_str[i] != 0)
	{
		MCAL_UART_SendNoBlock(TX_str[i]);
		i++;
	}
	else
	{
		i=1;
		flag_send= 1;
	}
}
