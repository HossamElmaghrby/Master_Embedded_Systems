/*
 * Atmega32_UART_Driver.h
 *
 * Created: 1/31/2024 1:32:41 PM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_UART_DRIVER_H_
#define ATMEGA32_UART_DRIVER_H_

#include "Atmega32_Device_Header.h"

void  MCAL_UART_init(void);
void  MCAL_UART_Send(uint8 data);
uint8 MCAL_UART_Receive(void) ;
void  MCAL_UART_SndNumberU32(uint32 NUM);
uint32 MCAL_UART_ReceiveNumberU32(void);
void MCAL_UART_Send_Str(char *str);
void MCAL_UART_Receive_Str(char *str);

#endif /* ATMEGA32_UART_DRIVER_H_ */