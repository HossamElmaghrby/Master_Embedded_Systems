/*
 * Atmega32_ADC_Driver.h
 *
 * Created: 4/25/2024 7:29:07 AM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_ADC_DRIVER_H_
#define ATMEGA32_ADC_DRIVER_H_

//======================Includes=====================//

#include "Atmega32_Device_Header.h"
#include "Atmega32_GPIO_Driver.h"


//======================Structures====================//

typedef struct
{
	uint8 Volt_Ref_Selec ;              // specifies Source of the reference Voltage (internal or external)
	                                    // This parameter set based on @ref ADC_Volt_Ref_define 

	uint8 Data_Store ;                   // Specifies How data Store in Data Register From right or left
	                                     // This parameter set based on @ref ACD_Data_Store_define 
										  
	uint8 Channel_and_Gain ;             // Specifies Channel number (ADC0-->ADC7) on PORTA and Gain in Case Differentrail input
	                                     // This parameter set based on @ref ADC_Channel_And_Gain_define
	
	uint8 Auto_Trigger_enable ;          // Specifies auto trigger enable or disable
	                                     // This parameter set base on @ref ADC_auto_Trigger_define 										
											
	uint8 Auto_Trigger_Source ;          // Specifies Witch action will start the trigger  Note. must auto_trigger is enable
	                                     // This parameter set based on @ref ADC_Trigger_Source_defien
    
	uint8 Interrupt_Enable ;             //Specifies enable the interrupt or disable
	                                     //This parameter set base on @ref ADC_Interrupt_define 

	uint8 Prescaler ;                    //Specifies the division factor between the XTAL frequency and the input clock to the ADC 
	                                     //This parameter set based on @ref ADC_Prescaler_define 

   void (*P_IRQ_CallBack)(void) ;        // C Function Call Back when Interrupt flag active 
}ADC_Config;

//===================Macros==================//

//ADMUX . Bit 7:6 – REFS1:0: Reference Selection Bits
//@ref ADC_Volt_Ref_define
#define ADC_Volt_Ref_External_AREF         (uint8)(0<<6)
#define ADC_Volt_Ref_Internal_AVCC         (uint8)(1<<6)
#define ADC_Volt_Ref_Internal_2560mV        (uint8)(3<<6)

//ADMUX .Bit 5 – ADLAR: ADC Left Adjust Result
//@ref ACD_Data_Store_define
#define ADC_Data_Store_Right_adj             (uint8)(0<<5)
#define ADC_Data_Store_Left_adj              (uint8)(1<<5)

//ADMUX .Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
//@ref ADC_Channel_And_Gain_define

#define ADC_Channel_And_Gain_Single_ADC0                    (uint8)(0b00000)
#define ADC_Channel_And_Gain_Single_ADC1                    (uint8)(0b00001)
#define ADC_Channel_And_Gain_Single_ADC2                    (uint8)(0b00010)
#define ADC_Channel_And_Gain_Single_ADC3                    (uint8)(0b00011)
#define ADC_Channel_And_Gain_Single_ADC4                    (uint8)(0b00100)
#define ADC_Channel_And_Gain_Single_ADC5                    (uint8)(0b00101)
#define ADC_Channel_And_Gain_Single_ADC6                    (uint8)(0b00110)
#define ADC_Channel_And_Gain_Single_ADC7                    (uint8)(0b00111)

#define ADC_Channel_And_Gain_differential_ADC1_0_Gx10       (uint8)(0b01001)
#define ADC_Channel_And_Gain_differential_ADC1_0_Gx200      (uint8)(0b01011)
#define ADC_Channel_And_Gain_differential_ADC3_2_Gx10       (uint8)(0b01101)
#define ADC_Channel_And_Gain_differential_ADC0_1_Gx1        (uint8)(0b10000)
#define ADC_Channel_And_Gain_differential_ADC1_1_Gx1        (uint8)(0b01001) 
#define ADC_Channel_And_Gain_differential_ADC2_1_Gx1        (uint8)(0b10010)
#define ADC_Channel_And_Gain_differential_ADC3_1_Gx1        (uint8)(0b10011)

#define ADC_Channel_And_Gain_Single_VGB                     (uint8)(0b11110)  
#define ADC_Channel_And_Gain_Single_0V                      (uint8)(0b11111)   


//ADCSRA . Bit 5 – ADATE: ADC Auto Trigger Enable
//@ref ADC_auto_Trigger_define
#define  ADC_auto_Trigger_Disable                            (uint8)(0<<5)
#define  ADC_auto_Trigger_Enable                             (uint8)(1<<5)   
 
//SFIOR  . Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
//@ref ADC_Trigger_Source_defien
#define ADC_Trigger_Source_Free_Running                      (uint8)(0<<5)
#define ADC_Trigger_Source_Analog_Comparator                 (uint8)(1<<5)
#define ADC_Trigger_Source_External_interrupt_Req0           (uint8)(2<<5)  
#define ADC_Trigger_Source_Timer0_Compare_Match              (uint8)(3<<5)  
#define ADC_Trigger_Source_Timer0_Overflow                   (uint8)(4<<5)
#define ADC_Trigger_Source_Timer1_Compare_Match_B            (uint8)(5<<5) 
#define ADC_Trigger_Source_Timer1_Overflow                   (uint8)(6<<5)
#define ADC_Trigger_Source_Timer1_Capture_Event              (uint8)(7<<5)

//ADCSRA .Bit 3 – ADIE: ADC Interrupt Enable
//@ref ADC_Interrupt_define
#define ADC_Interrupt_Disable                                (uint8)(0<<3)
#define ADC_Interrupt_Enable                                 (uint8)(1<<3)

//ADCSRA .Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
//@ref ADC_Prescaler_define
#define ADC_Prescaler_2                                      (uint8)(0)
#define ADC_Prescaler_4                                      (uint8)(2)
#define ADC_Prescaler_8                                      (uint8)(3)
#define ADC_Prescaler_16                                     (uint8)(4)
#define ADC_Prescaler_32                                     (uint8)(5)
#define ADC_Prescaler_64                                     (uint8)(6)
#define ADC_Prescaler_128                                    (uint8)(7)          





//ADCSRA . Bit 6 – ADSC: ADC Start Conversion
#define ADC_Stop_Conversion                          (uint8)(0<<6)
#define ADC_Start_Conversion                         (uint8)(1<<6)
//=============================APIs========================//

void MCAL_ADC_Init(ADC_Config *ADC_Cfg) ;
void MCAL_ADC_DeInit(void) ;

uint16 MCAL_ADC_Read();
 

#endif /* ATMEGA32_ADC_DRIVER_H_ */

