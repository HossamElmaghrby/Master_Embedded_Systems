/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Elmag
 */


#include "CortexMX_OS_Porting.h"

uint8_t SysTicks ;

void HardFault_Handler()
{
	while(1);
}
void MemManage_Handler()
{
	while(1);

}
void BusFault_Handler()
{
	while(1);

}
void UsageFault_Handler()
{
	while(1);

}

__attribute ((naked)) void SVC_Handler()
{
   __asm("TST LR ,#4 \n\t"
		   "ITE EQ \n\t"
		   "MRSEQ R0 ,MSP \n\t"
		   "MRSNE R0 ,PSP \n\t"
		   "B MYRTOS_SVC_Services");
}

void trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;

}

void HW_Init()
{
	//Initialize Clock Tree (RCC-> SysTick & CPU)
	//8MHZ
	//1 Count -> 0.125 us
	//x Count -> 1ms
	//x =8000 Count

	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15) ;
}

void Start_Ticker()
{
	//	This clock tree should be defined in HW_init()
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count

	 SysTick_Config(8000);


}

void SysTick_Handler(void)
{
	SysTicks^= 1 ;
    MYRTOS_Update_TasksWaitingTime();
	//Determine Pcurrent & Pnext
	Decide_WhatNext();
	//Switch Context & restore
	trigger_OS_PendSV();

}
