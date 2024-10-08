/*
 * STM32F103x6.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Elmag
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "stdlib.h"
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_Memory_BASE 							0x08000000UL
#define System_Memory_BASE 							0x1FFFF000UL
#define SRAM_Memory_BASE 							0x20000000UL


#define Peripherals_BASE 							0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE 		0xE0000000UL

//Nested vectored interrupt controller (NVIC)
#define NVIC_BASE_Add                                   0xE000E100UL

#define NVIC_ISER0                                  *(volatile uint32_t *)(NVIC_BASE_Add + 0x00)
#define NVIC_ISER1									*(volatile uint32_t *)(NVIC_BASE_Add + 0x04)
#define NVIC_ISER2                                  *(volatile uint32_t *)(NVIC_BASE_Add + 0x08)
#define NVIC_ICER0									*(volatile uint32_t *)(NVIC_BASE_Add + 0x80)
#define NVIC_ICER1									*(volatile uint32_t *)(NVIC_BASE_Add + 0x84)
#define NVIC_ICER2									*(volatile uint32_t *)(NVIC_BASE_Add + 0x88)

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
//RCC
#define RCC_BASE 							0x40021000UL
//#define RCC_BASE              				(Peripherals_BASE + 0x00021000UL)


//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------


//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE 							0x40010800UL
#define GPIOB_BASE 							0x40010C00UL


//C,D Partial  included in LQFP48 Package
#define GPIOC_BASE 							0x40011000UL
#define GPIOD_BASE 							0x40011400UL


//E not  included in LQFP48 Package
#define GPIOE_BASE 							0x40011800UL

//EXTI
#define EXTI_BASE 							0x40010400UL

//AFIO
#define AFIO_BASE 							0x40010000UL

#define USART1_BASE                         0x40013800UL


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

#define USART2_BASE                         0x40004400UL

#define USART3_BASE                         0x40004800UL

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t  CRL ;
	volatile uint32_t  CRH ;
	volatile uint32_t  IDR ;
	volatile uint32_t  ODR ;
	volatile uint32_t  BSRR ;
	volatile uint32_t  BRR ;
	volatile uint32_t  LCKR ;
}GPIO_TypeDef;





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t  CR ;
	volatile uint32_t  CFGR ;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t  IMR ;
	volatile uint32_t  EMR ;
	volatile uint32_t  RTSR;
	volatile uint32_t  FTSR ;
	volatile uint32_t  SWIER ;
	volatile uint32_t  PR ;

}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t  EVCR ;
	volatile uint32_t  MAPR ;
	volatile uint32_t  EXTICR[4] ;
	uint32_t  		   RESERVED0 ; //0x18
	volatile uint32_t  MAPR2 ; // 0x1c


}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


typedef struct
{
	 volatile uint32_t SR;
	 volatile uint32_t DR;
	 volatile uint32_t BRR;
	 volatile uint32_t CR1;
	 volatile uint32_t CR2;
	 volatile uint32_t CR3;
	 volatile uint32_t GTPR;
}USART_Typedef;

//==============================================================


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA      					((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB      					((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC      					((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD      					((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE      					((GPIO_TypeDef *)GPIOE_BASE)

#define RCC      					((RCC_TypeDef *)RCC_BASE)

#define EXTI      					((EXTI_TypeDef *)EXTI_BASE)

#define AFIO      					((AFIO_TypeDef *)AFIO_BASE)

#define USART1		            	((USART_Typedef*)USART1_BASE)
#define USART2			            ((USART_Typedef*)USART2_BASE)
#define USART3			            ((USART_Typedef*)USART3_BASE)

//==============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1<<0)

//USART
#define RCC_USART1_CLK_EN()	(RCC->APB2ENR |= 1 << 14)
#define RCC_USART2_CLK_EN()	(RCC->APB1ENR |= 1 << 17)
#define RCC_USART3_CLK_EN()	(RCC->APB1ENR |= 1 << 18)

/*
 * Disable clock
 */
#define RCC_USART1_CLK_DI()	(RCC->APB2RSTR |= 1 << 14)
#define RCC_USART2_CLK_DI()	(RCC->APB1RSTR |= 1 << 17)
#define RCC_USART3_CLK_DI()	(RCC->APB1RSTR |= 1 << 18)

//-*-*-*-*-*-*-*-*-*-*-*-
//Interrupt Vector Table:
//-*-*-*-*-*-*-*-*-*-*-*
/*
 * EXTI
 */

#define EXTI0_IRQ        6
#define EXTI1_IRQ        7
#define EXTI2_IRQ        8
#define EXTI3_IRQ        9
#define EXTI4_IRQ        10
#define EXTI5_IRQ        23
#define EXTI6_IRQ        23
#define EXTI7_IRQ        23
#define EXTI8_IRQ        23
#define EXTI9_IRQ        23
#define EXTI10_IRQ       40
#define EXTI11_IRQ       40
#define EXTI12_IRQ       40
#define EXTI13_IRQ       40
#define EXTI14_IRQ       40
#define EXTI15_IRQ       40

/*
 * USART
 */
#define USART1_IRQ		 37
#define USART2_IRQ		 38
#define USART3_IRQ		 39

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*--*-*-*-
//NVIC IRQ Enable/Disable Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-

/*  Enable Interrupt Requests  */

// We Started From IRQ6 Due To DataSheet
// ISER : Interrupt Set Register

#define NVIC_IRQ6_EXTI0_EN()			(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_EN()			(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_EN()			(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_EN()			(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_EN()			(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_EN()			(NVIC_ISER0 |= 1<<23)

// 40 - 32 = 8
#define NVIC_IRQ40_EXTI10_15_EN()		(NVIC_ISER1 |= 1<<8)

#define NVIC_IRQ37_USART1_EN()			(NVIC_ISER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_EN()			(NVIC_ISER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_EN()			(NVIC_ISER1 |= 1<<(USART3_IRQ - 32))

/* Disable Interrupt Requests */

// We Started From IRQ6 Due To DataSheet
// ICER : Interrupt Clear Register

#define NVIC_IRQ6_EXTI0_DI()			(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_DI()			(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_DI()			(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_DI()			(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_DI()			(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DI()			(NVIC_ICER0 |= 1<<23)

// 40 - 32 = 8
#define NVIC_IRQ40_EXTI10_15_DI()		(NVIC_ICER1 |= 1<<8)

#define NVIC_IRQ37_USART1_DI()			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_DI()			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_DI()			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32))


#endif /* INC_STM32F103X6_H_ */

