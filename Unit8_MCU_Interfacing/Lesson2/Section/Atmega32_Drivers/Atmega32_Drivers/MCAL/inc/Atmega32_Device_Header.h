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
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
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

//==============================================================


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-

#define GPIOA          ((GPIO_TypeDef_t*)GPIOA_BASE)
#define GPIOB          ((GPIO_TypeDef_t*)GPIOB_BASE)
#define GPIOC          ((GPIO_TypeDef_t*)GPIOC_BASE)
#define GPIOD          ((GPIO_TypeDef_t*)GPIOD_BASE)

#define EXTI           ((EXTI_Typedef_t*)EXTI_BASE)

#endif /* ATMEGA32_DEVICE_HEADER_H_ */