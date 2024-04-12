/*
 * Atmega32_GPIO_Driver.h
 *
 * Created: 12/14/2023 9:06:56 AM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_GPIO_DRIVER_H_
#define ATMEGA32_GPIO_DRIVER_H_

#include "Atmega32_Device_Header.h"

typedef struct
{
  uint8_t GPIO_PinNumber ;	// Specifies the GPIO pins to be configured.
                            // This parameter must be set based on @ref GPIO_PINS_define
							
  uint8_t GPIO_MODE  ;		// Specifies the operating mode for the selected pins
                            // This parameter must be a value of @ref GPIO_MODE_define				
}GPIO_PinConfig_t;

//================================
//Macros Configuration References
//================================

//@ref GPIO_PINS_define

#define GPIO_PIN_0                    ((uint8_t)0x01)
#define GPIO_PIN_1                    ((uint8_t)0x02)
#define GPIO_PIN_2                    ((uint8_t)0x04)
#define GPIO_PIN_3                    ((uint8_t)0x08)
#define GPIO_PIN_4                    ((uint8_t)0x10)
#define GPIO_PIN_5                    ((uint8_t)0x20)
#define GPIO_PIN_6                    ((uint8_t)0x40)
#define GPIO_PIN_7                    ((uint8_t)0x80)
#define GPIO_PIN_ALL                  ((uint8_t)0xFF)

//@ref GPIO_MODE_define

#define GPIO_MODE_INPUT_FLO        0 
#define GPIO_MODE_INPUT_PU         1 
#define GPIO_MODE_OUTPUT_PP        2 
#define GPIO_MODE_OUTPUT_OD        4            

//@ref GPIO_PIN_state
#define GPIO_PIN_SET    	1
#define GPIO_PIN_RESET      0

/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */
void MCAL_GPIO_Init(GPIO_TypeDef_t *GPIOx ,GPIO_PinConfig_t * PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef_t* GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef_t * GPIOx , uint8_t PinNumber ,uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef_t * GPIOx ,uint8_t Value);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *GPIOx ,uint8_t PinNumber);
uint8_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *GPIOx);

void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *GPIOx ,uint8_t PinNumber);

#endif /* ATMEGA32_GPIO_DRIVER_H_ */