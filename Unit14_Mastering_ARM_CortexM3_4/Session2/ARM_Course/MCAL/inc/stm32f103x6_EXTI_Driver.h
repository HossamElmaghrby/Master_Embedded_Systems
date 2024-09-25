/*
 * stm32f103x6_EXTI_Driver.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Elmag
 */

#ifndef INC_STM32F103X6_EXTI_DRIVER_H_
#define INC_STM32F103X6_EXTI_DRIVER_H_



/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_Driver.h"

/* ================================================================ */
/* ========== User type definitions (structures) ================== */
/* ================================================================ */

typedef struct
{
	uint8_t EXTI_InputLineNumber  ;    //choose Line Number To use in EXTI

	//GPIO_TypeDef *GPIO_Port     ;    //choose port for EXTI

	uint16_t GPIO_Pin             ;    //choose pin to use in EXTI

	uint8_t IVT_IRQ_Number        ;    // choose interrupt handler from interrupt vector table

}EXTI_GPIO_Mapping_t;

typedef struct
{
	EXTI_GPIO_Mapping_t EXTI_PIN ;     // Specifics the EXTI GPIO Mapping
	                                   // This parameter must be set based on @ref EXTI_define

	GPIO_TypeDef *GPIO_Port     ;      //choose port for EXTI

	uint8_t  trigger_case       ;      // Specifics RISING or FALLING or Both trigger
	                                   // This parameter must be set based on @ref EXTI_Trigger_define

	uint8_t  IRQ_Enable         ;       // Enable or Disable the EXTI IRQ (That will enable the IRQ mask in EXTI and also on the NVIC Interrupt contoller)
	                                    // This parameter must be set based on @ref EXTI_IRQ_define

	void(*P_IRQ_CallBack)(void);		// Set the c Function() which will be called once the IRQ happen
}EXTI_PinConfig_t;

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */

//@ref EXTI_define

#define EXTI_Pin0        (EXTI_GPIO_Mapping_t){EXTI0,GPIO_PIN_0, EXTI0_IRQ}

#define EXTI_Pin1        (EXTI_GPIO_Mapping_t){EXTI1,GPIO_PIN_1, EXTI1_IRQ}

#define EXTI_Pin2        (EXTI_GPIO_Mapping_t){EXTI2,GPIO_PIN_2, EXTI2_IRQ}

#define EXTI_Pin3 		 (EXTI_GPIO_Mapping_t){EXTI3,GPIO_PIN_3, EXTI3_IRQ}

#define EXTI_Pin4 		 (EXTI_GPIO_Mapping_t){EXTI4,GPIO_PIN_4, EXTI4_IRQ}

#define EXTI_Pin5        (EXTI_GPIO_Mapping_t){EXTI5,GPIO_PIN_5, EXTI5_IRQ}

#define EXTI_Pin6        (EXTI_GPIO_Mapping_t){EXTI6,GPIO_PIN_6, EXTI6_IRQ}

#define EXTI_Pin7        (EXTI_GPIO_Mapping_t){EXTI7,GPIO_PIN_7, EXTI7_IRQ}

#define EXTI_Pin8        (EXTI_GPIO_Mapping_t){EXTI8,GPIO_PIN_8, EXTI8_IRQ}

#define EXTI_Pin9        (EXTI_GPIO_Mapping_t){EXTI9,GPIO_PIN_9, EXTI9_IRQ}

#define EXTI_Pin10       (EXTI_GPIO_Mapping_t){EXTI10,GPIO_PIN_10,EXTI10_IRQ}

#define EXTI_Pin11       (EXTI_GPIO_Mapping_t){EXTI11,GPIO_PIN_11, EXTI11_IRQ}

#define EXTI_Pin12       (EXTI_GPIO_Mapping_t){EXTI12,GPIO_PIN_12, EXTI12_IRQ}

#define EXTI_Pin13       (EXTI_GPIO_Mapping_t){EXTI13,GPIO_PIN_13, EXTI13_IRQ}

#define EXTI_Pin14       (EXTI_GPIO_Mapping_t){EXTI14,GPIO_PIN_14, EXTI14_IRQ}

#define EXTI_Pin15       (EXTI_GPIO_Mapping_t){EXTI15,GPIO_PIN_15, EXTI15_IRQ}


//@ref EXTI_Trigger_define

#define EXTI_Trigger_Rising		        0
#define EXTI_Trigger_Faling		        1
#define EXTI_Trigger_RisingANDFaling  	2


//@ref EXTI_IRQ_define
#define EXTI_IRQ_Enable					1
#define EXTI_IRQ_Disable				0

/*
 * Configuration reference
 */
#define EXTI0		0
#define EXTI1		1
#define EXTI2		2
#define EXTI3		3
#define EXTI4		4
#define EXTI5		5
#define EXTI6		6
#define EXTI7		7
#define EXTI8		8
#define EXTI9		9
#define EXTI10		10
#define EXTI11		11
#define EXTI12		12
#define EXTI13		13
#define EXTI14		14
#define EXTI15		15

/* ================================================================ */
/* ============== APIs Supported by "MCAL ..... DRIVER" =========== */
/* ================================================================ */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config) ;
void MCAL_EXTI_GPIO_Deinit(void);
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config) ;



#endif /* INC_STM32F103X6_EXTI_DRIVER_H_ */
