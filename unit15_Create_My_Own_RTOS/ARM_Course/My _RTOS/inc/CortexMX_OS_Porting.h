/*
 * CortexMX_OS_Porting.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Elmag
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_


#include "core_cm3.h"

#define OS_SET_PSP(add)      	 	__asm("MOV r0 , %0  \n\t MSR PSP , r0" : : "r" (add))
#define OS_GET_PSP(add)       		__asm("MRS r0 , PSP \n\t MOV %0 , r0" : "=r" (add))


#define OS_SWITCH_To_SP_PSP       		__asm("MRS r0 ,CONTROL \n\t MOV r1 , #0x02 \n\t ORR r0,r0,r1 \n\t MSR CONTROL ,r0")
#define OS_SWITCH_SP_MSP       		__asm("MRS r0 ,CONTROL \n\t MOV r1 , #0x05 \n\t AND r0,r0,r1 \n\t MSR CONTROL ,r0")

#define OS_SWITCH_To_Privilage		__asm("MRS r0 ,CONTROL  \n\t"\
									"LSR r0 ,r0 ,#0x1 \n\t" \
									"LSL r0 ,r0 ,#0x1 \n\t" \
									"MSR CONTROL , r0")

#define OS_SWITCH_To_Unprivilage   	__asm("MRS r0 , CONTROL \n\t" \
									"ORR r0 ,r0 ,#0x1 \n\t" \
									"MSR CONTROL , r0")

extern uint32_t _estack ;
extern uint32_t _eheap ;

#define MainStackSize  2048 ;

void HW_Init();
void Start_Ticker();
void trigger_OS_PendSV();
void Decide_WhatNext();
#endif /* INC_CORTEXMX_OS_PORTING_H_ */
