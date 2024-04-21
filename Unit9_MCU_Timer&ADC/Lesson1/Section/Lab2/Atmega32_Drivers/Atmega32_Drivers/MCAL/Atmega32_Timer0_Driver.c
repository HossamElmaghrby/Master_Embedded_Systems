/*
 * Atmega32_Timer0_Driver.c
 *
 * Created: 4/19/2024 10:13:08 AM
 *  Author: Elmag
 */ 

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "Atmega32_Timer0_Driver.h"

Timer0_Config G_timer0_Cfg ;

/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */


/* ================================================================
 * @Fn 				- MCAL_Timer0_Init
 * @brief 			- Initializes Timer0 according to the specified parameters in Timer0_Cfg
 * @param [in] 		- Timer0_Config : a pointer to Timer0_Config structure that contains the configuration information for the specified TIMER Module
 * @retval 			- None
 * Note 			- Supported for TIMER0 ONLY
 *
 */
void MCAL_Timer0_Init(Timer0_Config * Timer0_Cfg)
{
      G_timer0_Cfg = *Timer0_Cfg ;
	  
	  // Select mode timer
	  TCCR0 |= Timer0_Cfg->Timer0_Mode ;
	 
	 
	 if(Timer0_Cfg->Output_Compare != Timer0_OC_disconnected)
	 {
		 
		 //Configure 0C0 (PINB3) as Output
		 DDRB |=(1<<3);
		 //type of output compare
		 TCCR0 |= Timer0_Cfg->Output_Compare ;
	 } 
	 
	 //Select Clock Source
	 TCCR0 |= Timer0_Cfg->Clock_Select ;
	 
	 if(Timer0_Cfg->Clock_Select == Timer0_Clock_External_Falling_Edge || Timer0_Clock_External_Rising_Edge)
	 {
		 // Configure T0 (PINB0) as Input
		 DDRB &= ~(1<<0);
	 }
	 
	 //Enable Interrupt
	 TIMSK |= Timer0_Cfg->IRQ_Enable ;
	 
	 if(Timer0_Cfg->IRQ_Enable != Timer0_IRQ_NONE)
	 {
		 Enable_Global_Interrupt();
	 }
}

/* ================================================================
 * @Fn 				- MCAL_Timer0_DeInit
 * @brief 			- DeInitialze Timer0 Operation By Disable Timer Clock
 * @retval 			- None
 * Note 			- Supported for Timer0 ONLY
 */
void MCAL_Timer0_DeInit()
{
	TCCR0 = 0x00 ;
	TCNT0 = 0 ;
	OCR0  = 0 ;
	TIMSK = 0x00 ;
	TIFR  = 0x00 ;
	
}

/* ================================================================
 * @Fn 				- MCAL_Timer0_Set_Compare_Value
 * @brief 			- Set OCR Register compare Value in Compare Match Mode(CTC)
 * @param [in] 		- TicksNumber : Value to Set in OCR(compare value must not exceed 255)
 * @retval 			- None
 * Note 			- Supported for Compare Match Mode(CTC) only & compare value must not exceed 255
 */
void MCAL_Timer0_Set_Compare_Value(uint8_t TicksNumber)
{
	OCR0 = TicksNumber ;
}

/* ================================================================
 * @Fn 				- MCAL_Timer0_Get_Compare_Value
 * @brief 			- Set OCR Register compare Value in Compare Match Mode(CTC)
 * @param [in] 		- TicksNumber : Value to Set in OCR(compare value must not exceed 255)
 * @retval 			- None
 * Note 			- Supported for Compare Match Mode(CTC) only & compare value must not exceed 255
 */
void MCAL_Timer0_Get_Compare_Value(uint8_t *TicksNumber)
{
	*TicksNumber = OCR0 ;
}

/* ================================================================
 * @Fn 				- MCAL_Timer0_Set_Counter_Value
 * @brief 			- Set Timer counter value
 * @param [in] 		- TicksNumber : value of counter value from counter register (TCNT0)
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_Timer0_Set_Counter_Value(uint8_t TicksNumber)
{
	TCNT0 = TicksNumber ;
}
/* ================================================================
 * @Fn 				- MCAL_Timer0_Get_Counter_Value
 * @brief 			- Get Timer counter value
 * @param [in] 		- TicksNumber : value of counter value from counter register (TCNT0)
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_Timer0_Get_Counter_Value(uint8_t *TicksNumber)
{
	*TicksNumber =TCNT0 ;
}

/* OVERFLOW ISR */
ISR(TIMER0_OVF_vect)
{
	G_timer0_Cfg.P_IRQ_CallBack();
}

/* COMPARE MATCH ISR */
ISR(TIMER0_COMP_vect)
{
	G_timer0_Cfg.P_IRQ_CallBack();
}