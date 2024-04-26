/*
 * Atmega32_Timer0_Driver.h
 *
 * Created: 4/19/2024 10:12:25 AM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_TIMER0_DRIVER_H_
#define ATMEGA32_TIMER0_DRIVER_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "Atmega32_Device_Header.h"
#include "avr/interrupt.h"


/* ================================================================ */
/* ============= User type definitions (structures) =============== */
/* ================================================================ */

typedef struct  
{
	uint8_t Timer0_Mode ;             // specifies timer mode (normal or CTC mode or fast PWM or phase correct)
	                                  // this parameter set based on @ref Timer0_Mode_Defien 
	
	uint8_t Output_Compare ;          // specifies output of OC pin (disconnected or toggle or clear or set)
	                                  // this parameter set based on @ref Timer0_OC_Defien
	
	uint8_t Clock_Select ;            //specifies clock pulse (internal or external) and prescaler(no or 8 or 64 or 256 or ...)
	                                  //this parameter set based on @ref Timer0_Clock_Defien         								       
	
    uint8_t IRQ_Enable ;              // specifies Interrupt request (compare match or overflow)
	                                  // this parameter set based in @ref Timer0_IRQ_define  	
    
	void (*P_IRQ_CallBack)(void);     // point to C function to CallBack Interrupt
}Timer0_Config;

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */


//@ref Timer0_Mode_Defien 
#define Timer0_Mode_Normal           (uint8_t)(0)
#define Timer0_Mode_Ph_Cor_PWM       (uint8_t)(1<<6) 
#define Timer0_Mode_CTC              (uint8_t)(1<<3)
#define Timer0_Mode_Fast_PWM         (uint8_t)((1<<3)|(1<<6))

//@ref Timer0_OC_Defien
#define Timer0_OC_disconnected       (uint8_t)(0)
#define Timer0_OC_Toggle             (uint8_t)(1<<4)   //note this valid in Normal or CTC mode only
#define Timer0_OC_Clear              (uint8_t)(1<<5)
#define Timer0_OC_Set                (uint8_t)((1<<4) | (1<<5))

// @ref Timer0_Clock_Defien
#define Timer0_Clock_Stop                         (uint8_t)(0)
#define Timer0_Clock_Internal_No_Prescaler        (uint8_t)(0x01) 
#define Timer0_Clock_Internal_Prescaler_8         (uint8_t)(0x02)
#define Timer0_Clock_Internal_Prescaler_64        (uint8_t)(0x03)
#define Timer0_Clock_Internal_Prescaler_256       (uint8_t)(0x04)
#define Timer0_Clock_Internal_Prescaler_1024      (uint8_t)(0x05)
#define Timer0_Clock_External_Falling_Edge        (uint8_t)(0x06)
#define Timer0_Clock_External_Rising_Edge         (uint8_t)(0x07)

//@ref Timer0_IRQ_define
#define Timer0_IRQ_NONE                           (uint8_t)(0) 
#define Timer0_IRQ_Compare_Match_Enable           (uint8_t)(1<<1)
#define Timer0_IRQ_Overflow_Enable                (uint8_t)(1<<0)

/* ================================================================ */
/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */
/* ================================================================ */

void MCAL_Timer0_Init(Timer0_Config * Timer0_Cfg);
void MCAL_Timer0_DeInit();

void MCAL_Timer0_Set_Compare_Value(uint8_t TicksNumber);
void MCAL_Timer0_Get_Compare_Value(uint8_t *TicksNumber);

void MCAL_Timer0_Set_Counter_Value(uint8_t TicksNumber);
void MCAL_Timer0_Get_Counter_Value(uint8_t *TicksNumber);


#endif /* ATMEGA32_TIMER0_DRIVER_H_ */