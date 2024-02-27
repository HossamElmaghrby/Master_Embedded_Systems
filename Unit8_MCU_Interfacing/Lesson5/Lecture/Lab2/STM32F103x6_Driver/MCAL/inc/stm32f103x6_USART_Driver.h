/*
 * stm32f103x6_USART_Driver.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Elmag
 */

#ifndef INC_STM32F103X6_USART_DRIVER_H_
#define INC_STM32F103X6_USART_DRIVER_H_

#include "STM32F103x6.h"
#include "stm32f103x6_RCC_Driver.h"
#include "stm32f103x6_GPIO_Driver.h"

typedef struct
{
	uint8_t     USART_Mode ;           //Specifies TX/RX Enable/Disable
 	                                   // This parameters must be set based on @Ref UART_Mode_define

	uint32_t    BaudRate   ;           // This member to configure the Baud Rate
	                                   // This parameters must be set based on @Ref UART_BaudRate_define

    uint8_t     Payload_Length ;       // Specifies the number of data bits transmitted or received in a frame
	                                   // This parameters must be set based on @Ref UART_Payload_Length_define

    uint8_t     parity ;               // Specifies the parity mode
                                       // This parameters must be set based on @Ref UART_Parity_define

    uint8_t     StopBit ;              // Specifies the number of stop bits
	                                   // This parameters must be set based on @Ref UART_StopBits_define

    uint8_t		HwFlowCtl ;			   // Specifies whether the hardware flow control mode is enabled or disabled
    								   // This parameters must be set based on @Ref UART_HwFlowCtl_define

    uint8_t    IRQ_Enable ;            // enable or disable the interrupt
	                                   // This parameters must be set based on @Ref UART_IRQ_define

   void(* P_IRQ_CallBack)(void);       // Set the C Function() which will be called once the IRQ Happen

}USART_Config;

//===========================================================
//================Macros configuration References============
//===========================================================

//@Ref UART_Mode_define

#define USART_Mode_TX               (uint32_t)(1<<3)
#define USART_Mode_RX               (uint32_t)(1<<2)
#define USART_Mode_TX_AND_RX        (uint32_t)(1<<2 | 1<<3)

//@Ref UART_BaudRate_define
#define USART_BaudRate_2400			2400
#define USART_BaudRate_9600			9600
#define USART_BaudRate_19200		19200
#define USART_BaudRate_57600		57600
#define USART_BaudRate_115200		115200
#define USART_BaudRate_230400		230400
#define USART_BaudRate_460800		460800
#define USART_BaudRate_921600		921600
#define USART_BaudRate_225000		2250000
#define USART_BaudRate_4500000		4500000

//@Ref UART_Payload_Length_define
#define USART_Payload_Length_8B     (uint32_t)(0)
#define USART_Payload_Length_9B     (uint32_t)(1<<12)

//@Ref UART_Parity_define
#define USART_Parity_NONE            (uint32_t)(0)
#define USART_Parity_EVEN           (uint32_t)(1<<10)
#define USART_Parity_ODD            (uint32_t)(1<<10 | 1<<9)

// @Ref UART_StopBits_define
#define USART_StopBits_half         (uint32_t)(1<<12)
#define USART_StopBits_1            (uint32_t)(0)
#define USART_StopBits_1_half       (uint32_t)(3<<12)
#define USART_StopBits_2            (uint32_t)(2<<12)

// @Ref UART_HwFlowCtl_define
#define USART_HwFlowCtl_NONE		(uint32_t)(0)
#define USART_HwFlowCtl_RTS			(uint32_t)(1<<8)
#define USART_HwFlowCtl_CTS			(uint32_t)(1<<9)
#define USART_HwFlowCtl_RTS_CTS		(uint32_t)(1<<8 | 1<<9)

//@Ref UART_IRQ_define
#define USART_IRQ_Enable_NONE		(uint32_t)(0)
#define USART_IRQ_Enable_TXE		(uint32_t)(1<<7)	// Transmit data register empty
#define USART_IRQ_Enable_TC			(uint32_t)(1<<6)	// Transmission complete
#define USART_IRQ_Enable_RXNEIE		(uint32_t)(1<<5)	// Received data ready to be read
#define USART_IRQ_Enable_PE         (uint32_t)(1<<8)	// Parity error


enum polling_Mechanism
{
    disable,
	enable
};

//=================BaudRate Calculation==========================

// USARTDIV = fclk / (16 * Baudrate)
// USARTDIV_MUL100 = uint32((100 * fclk ) / ( 16 * Baudrate) == (25 * fclk) / (4 * Baudrate))
// DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
// DIV_Mantissa = Integer Part (USARTDIV)
// DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) *16) / 100

#define USARTDIV(_PCLK_ ,_BAUD_)                      (uint32_t) (_PCLK_/(16*_BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)               (uint32_t) ((_PCLK_ * 25)/(_BAUD_ * 4))
#define Mantissa_MUL100(_PCLK_, _BAUD_)			      (uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)				      (uint32_t) (USARTDIV(_PCLK_, _BAUD_ ))
#define DIV_Fraction(_PCLK_, _BAUD_)                  (uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_)-Mantissa_MUL100(_PCLK_, _BAUD_))*16) / 100)
#define USART_BRR_Register(_PCLK_, _BAUD_)		(( Mantissa (_PCLK_, _BAUD_ ) ) << 4 )|((DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )

//===============================================================
//-----------------APIs Supported by "MCAL USART DRIVER"---------
//===============================================================

void MCAL_USART_Init(USART_Typedef * USARTx , USART_Config * USART_cfg);
void MCAL_USART_DeInit(USART_Typedef * USARTx);

void  MCAL_USART_GPIO_Set_Pins(USART_Typedef * USARTx);

void MCAL_USART_sendData(USART_Typedef * USARTx,uint16_t * pTxBuffer , enum polling_Mechanism pollingEn);
void MCAL_USART_ReceiveData(USART_Typedef * USARTx,uint16_t * pRxBuffer , enum polling_Mechanism pollingEn);
void MCAL_UART_WAIT_TC(USART_Typedef* USARTx);
// TODO MCAL_USART_LIN_Init()	// LIN
// TODO MCAL_USART_Init()		// Synchronous
// TODO MCAL_USART_DMA_Init()	// Multi-buffer communication

#endif /* INC_STM32F103X6_USART_DRIVER_H_ */
