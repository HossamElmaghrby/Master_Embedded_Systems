/*
 * Atmega32_GPIO_Driver.c
 *
 * Created: 12/14/2023 9:08:58 AM
 *  Author: Elmag
 */ 
#include "Atmega32_GPIO_Driver.h"

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in] 	-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
 *         		 the configuration information for the specified GPIO PIN.
 * @retval 		-none
 */
void MCAL_GPIO_Init(GPIO_TypeDef_t *GPIOx ,GPIO_PinConfig_t * PinConfig)
{
	if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP ||PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD)
	{
		//set DDR x PIN n
		GPIOx->DDR  |=(PinConfig->GPIO_PinNumber);
		
		if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)
		{
			//Reset PORTx PINy
			GPIOx->PORT &=~(PinConfig->GPIO_PinNumber);
		}
		else
		{
			//set PORTx PINy
			GPIOx->PORT |=(PinConfig->GPIO_PinNumber);
		}
	}
	else if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO || PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
	{
		//Reset DDR x PIN n
		GPIOx->DDR  &=~(PinConfig->GPIO_PinNumber);
		if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO)
		{
			//Reset PORTx PINy
			GPIOx->PORT &=~(PinConfig->GPIO_PinNumber);				
		}
		else
		{
			//set PORTx PINy
			GPIOx->PORT |=(PinConfig->GPIO_PinNumber);			
		}		
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-reset all the GPIO Register
 * @param [in] 	-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 * @retval 		-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef_t* GPIOx)
{
	GPIOx->DDR =0x00 ;
	GPIOx->PIN =0x00 ;
	GPIOx->PORT=0x00 ;
}

/**================================================================
 * @Fn					-MCAL_GPIO_WritePin
 * @brief 				-write on specific input pin
 * @param [in] 			-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 *@param [in] 			-PinNumber:  specifies the port bit to read. Set by @ref GPIO_PINS_define
 *@param [in] 			-Value: Pin Value
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef_t * GPIOx , uint8_t PinNumber ,uint8_t Value)
{
    if(Value == GPIO_PIN_SET)	
	{
		GPIOx->PORT |= (uint8_t)PinNumber ;
	}
	else
	{
		GPIOx->PORT &=~((uint8_t)PinNumber);
	}
	
}

/**================================================================
 * @Fn					-MCAL_GPIO_WritePort
 * @brief 				-write on output port
 * @param [in] 			-GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  *@param [in] 			-Value: port Value
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef_t * GPIOx ,uint8_t Value)
{
	GPIOx->PORT = (uint8_t)Value ;
}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief 			-Read Specific PIN
 * @param [in] 	-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval 		-the input pin value (two values based on @ref GPIO_PIN_state )
 * Note			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef_t *GPIOx ,uint8_t PinNumber)
{
	uint8_t binStatus ;
	
	binStatus =(GPIOx->PIN & PinNumber)?(uint8_t)GPIO_PIN_SET:(uint8_t)GPIO_PIN_RESET;
	
	return binStatus ;
}

/**================================================================
 * @Fn					-MCAL_GPIO_ReadPort
 * @brief 				-read the input port VALUE
 * @param [in] 			-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 * @retval 				-the input port VALUE
 * Note					-none
 */
uint8_t MCAL_GPIO_ReadPort(GPIO_TypeDef_t *GPIOx)
{
	
	uint8_t Port_Value ;
	
	Port_Value = (uint8_t)(GPIOx->PIN &0xFF) ;
	
	return Port_Value ;
}

/**================================================================
 * @Fn					-MCAL_GPIO_TogglePin
 * @brief 				-Toggles the specified GPIO pin
 * @param [in] 			-GPIOx: where x can be (A..D depending on device used) to select the GPIO peripheral
 * @param [in] 			-PinNumber: specifies the port bit to read. Set by @ref GPIO_PINS_define
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef_t *GPIOx ,uint8_t PinNumber)
{
	GPIOx->PORT ^=(PinNumber) ;
}