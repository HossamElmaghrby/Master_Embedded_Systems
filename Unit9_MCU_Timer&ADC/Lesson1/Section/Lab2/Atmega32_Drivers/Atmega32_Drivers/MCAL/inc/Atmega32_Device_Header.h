/*
 * Atmega32_Device_Header.h
 *
 * Created: 12/14/2023 9:08:06 AM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_DEVICE_HEADER_H_
#define ATMEGA32_DEVICE_HEADER_H_

//-----------------------------
//Includes
//-----------------------------

#include "Platform_Types.h"
#include "Utils.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY            0x00
#define SRAM                    0x60 

//-----------------------------
//Base addresses for Peripherals
//-----------------------------

//GPIO
#define GPIOA_BASE          0x39UL
#define GPIOB_BASE          0x36UL
#define GPIOC_BASE          0x33UL
#define GPIOD_BASE          0x30UL

//EXTI
#define EXTI_BASE 		    0x54UL

//UART
#define UART_BASE           0x29UL

//SPI
#define SPI_BASE            0x2DUL
//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint8_t PIN  ;
	volatile uint8_t DDR  ;
	volatile uint8_t PORT ;	
}GPIO_TypeDef_t; 

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
    volatile uint8_t  _MCUCSR    ;
	volatile uint8_t  _MCUCR     ;
	         uint32_t _reserved0 ;
	volatile uint8_t  _GIFR      ;
	volatile uint8_t  _GICR	     ;
}EXTI_TypeDef_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: UART
//-*-*-*-*-*-*-*-*-*-*-*-
//==============================================================

typedef struct
{
	uint8  _UBRRL ;
	uint8  _UCSRB ;
	uint8  _UCSRA ;
	uint8  _UDR ;
    uint64 _reserved0;
	uint64 _reserved1;
	uint16 _reserved2;
	uint8  _reserved3;
 union RC_RH
	{
		uint8  _UCSRC ;
		uint8  _UBRRH ;
	}RC_RH; 
	
}UART_TypeDef_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*-
//==============================================================

typedef struct
{
  uint8 _SPCR ;
  uint8 _SPSR ;
  uint8 _SPDR ;	
}SPI_TypeDef_t;



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-

#define GPIOA          ((GPIO_TypeDef_t*)GPIOA_BASE)
#define GPIOB          ((GPIO_TypeDef_t*)GPIOB_BASE)
#define GPIOC          ((GPIO_TypeDef_t*)GPIOC_BASE)
#define GPIOD          ((GPIO_TypeDef_t*)GPIOD_BASE)

#define EXTI           ((EXTI_TypeDef_t*)EXTI_BASE)

#define UART1          ((UART_TypeDef_t*)UART_BASE)

#define SPI1           ((SPI_TypeDef_t*)SPI_BASE)

//Global Interrupt
#define SREG                       *((uint8*)0x5FUL)

#define Enable_Global_Interrupt()    SREG |=(1<<7)
#define Disable_Global_Interrupt()   SREG &=~(1<<7)
#endif /* ATMEGA32_DEVICE_HEADER_H_ */