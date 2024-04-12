/*
 * Atmega32_UART_Driver.h
 *
 * Created: 1/31/2024 1:32:41 PM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_UART_DRIVER_H_
#define ATMEGA32_UART_DRIVER_H_

#include "Atmega32_Device_Header.h"

typedef struct 
{
	uint8    USART_Mode ; //TX or RX or TX_RX  based on  @Ref UART_Mode_define
	
	uint32   BaudRate ;   // this parameter set based on @Ref UART_BaudRate_define 
	
	uint8    data_size ;  // this parameter set based on @Ref UART_data_Size_define
	
    uint8    parity ;	 // this parameter set based on   @Ref UART_Parity_define
	
	uint8    StopBit ;   // this parameter set based on   @Ref UART_StopBits_define
	
	uint8    IRQ_Enable ; // this parameter set based on   @Ref UART_IRQ_define
	
	uint8   Speed_Mode ;  // this parameter set based on   @Ref  UART_Speed_Mode_define
	
	void(* P_IRQ_CallBack)(void); // Set the C Function() which will be called once the IRQ Happen
	
}UART_config;
//=====================Macros=====================

// @Ref UART_Mode_define
#define UART_Mode_TX               (uint8)(1<<4)
#define UART_Mode_RX               (uint8)(1<<3)
#define UART_Mode_TX_AND_RX        (uint8)(1<<3 | 1<<4)


//@Ref UART_BaudRate_define
#define UART_BaudRate_2400		2400
#define UART_BaudRate_4800		4800
#define UART_BaudRate_9600		9600
#define UART_BaudRate_14400	    14400
#define UART_BaudRate_19200	    19200
#define UART_BaudRate_28800	    28800
#define UART_BaudRate_14400	    14400
#define UART_BaudRate_38400	    38400
#define UART_BaudRate_57600	    57600
#define UART_BaudRate_76800	    76800

//@Ref UART_data_Size_define
#define UART_data_Size_5B             1
#define UART_data_Size_6B             2  
#define UART_data_Size_7B             3
#define UART_data_Size_8B             4
#define UART_data_Size_9B             5

//@Ref UART_StopBits_define
#define UART_StopBits_1            (uint8)(0)
#define UART_StopBits_2            (uint8)(1<<3)

//@Ref UART_Parity_define
#define UART_Parity_NONE            (uint8)(0)
#define UART_Parity_EVEN           (uint8)(2<<4)
#define UART_Parity_ODD            (uint8)(3<<4)


//@Ref  UART_Speed_Mode_define
#define UART_Speed_Mode_Normal              (uint8)(0)
#define UART_Speed_Mode_Double              (uint8)(1<<1)

//@Ref UART_IRQ_define   
#define  UART_Interrupt_Enable_NONE       (uint8)(0)
#define  UART_Interrupt_Enable_TXCIE      (uint8)(1<<6) 
#define  UART_Interrupt_Enable_RXCIE      (uint8)(1<<7) 
#define  UART_Interrupt_Enable_UDRIE      (uint8)(1<<5) 

//BaudRate
#define BAUD(_Fose_ ,_BAUD_ ,_Frac_)                (uint32)(((_Fose_/_BAUD_)/_Frac_)-1)  
                          
void   MCAL_UART_init(UART_TypeDef_t *UARTx , UART_config *UART_cfg);
void   MCAL_UART_Send(uint8 data);
uint8  MCAL_UART_Receive(void) ;
void   MCAL_UART_SndNumberU32(uint32 NUM);
uint32 MCAL_UART_ReceiveNumberU32(void);
void   MCAL_UART_Send_Str(uint8 *str);
void   MCAL_UART_Receive_Str(uint8 *str);
uint8  MCAL_UART_Receive_perodicCheck( uint8 *data);
void   MCAL_UART_SendNoBlock(uint8 data);
uint8  MCAL_UART_ReceiveNoBlock(void);
void   MCAL_UART_SendString_Asynch(uint8 * str);
#endif /* ATMEGA32_UART_DRIVER_H_ */