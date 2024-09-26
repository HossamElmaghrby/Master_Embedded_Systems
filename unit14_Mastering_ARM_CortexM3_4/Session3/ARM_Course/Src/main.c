/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_Driver.h"
#include "stm32f103x6_EXTI_Driver.h"
#include "LCD/LCD.h"
#include "Keypad/Keypad.h"

unsigned int flag = 0 ;
void delay(int delay)
{
	uint32_t i,j;

	for (i = 0; i < delay; i++)
	{
		for(j = 0; j < 255 ; j++);
	}
}
int IPSR = 0 ;
void EXTI9_CallBack()
{
  flag =1 ;
    __asm("nop \n\t nop");

	__asm("mrs %0 , IPSR"
			:"=r" (IPSR));
	__asm("nop \n\t nop");

}

int VAL1 = 8 ;
int VAL2 = 3 ;
int VAL3 =0 ;

int control = 0 ;

int main(void)
{
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;


	EXTI_PinConfig_t EXTI_RQ ;

	EXTI_RQ.EXTI_PIN =EXTI_Pin9 ;
	EXTI_RQ.GPIO_Port =GPIOB ;
	EXTI_RQ.trigger_case =EXTI_Trigger_Rising ;
	EXTI_RQ.P_IRQ_CallBack =EXTI9_CallBack ;
	EXTI_RQ.IRQ_Enable =EXTI_IRQ_Enable ;

	MCAL_EXTI_GPIO_Init(&EXTI_RQ) ;


	__asm("nop \n\t nop");

	__asm("add %0 ,%1 ,%2 "
			: "=r"(VAL3)
			: "r" (VAL1) , "r" (VAL2));

	__asm("nop \n\t nop");

	__asm("nop \n\t nop");

	__asm("mrs %0 , CONTROL"
			:"=r" (control));
	__asm("nop \n\t nop");


	while(1)
	{
      if(flag)
      {
    	  LCD_clear_screen();
    	  flag =0 ;
      }
	}
}