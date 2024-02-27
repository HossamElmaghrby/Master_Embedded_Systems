/*
 * stm32f103x6_USART_Driver.c
 *
 *  Created on: Feb 7, 2024
 *      Author: Elmag
 */

//================includes================

#include "stm32f103x6_USART_Driver.h"

//=====================public APIs==============================


/*
 * @Fn                -MCAL_USART_Init
 * @brief             -Initialize USART as Asynchronous only
 * @param [in]        -USARTx: where x can be (1..3 depending on device used)
 * @param [in]        -USART_cfg: All USART configuration
 * @retval            -none
 * Note               -support for now Asynchronous mode & clock 8MHZ
 */

USART_Config * Global_USART_config[3] = {NULL};
void MCAL_USART_Init(USART_Typedef * USARTx , USART_Config * USART_cfg)
{
	uint32_t pclk , BRR ;

	/* 1. Enable the clock for given USART peripheral */
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		Global_USART_config[0] = USART_cfg ;
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else if(USARTx ==  USART2)
	{
		RCC_USART2_CLK_EN();
		Global_USART_config[1] = USART_cfg ;
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		Global_USART_config[2] = USART_cfg;
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	/* 2. Enable USART Module */
	USARTx->CR1 |= 1<<13 ;                            // bit 13 UE: USART enable

	/* 3. Enable USART TX/RX engines according to the USART_Mode configuration item */
	USARTx->CR1 |=USART_cfg->USART_Mode ;            // USART_CR1 bit 3 TE: transmitter enable & bit 2 RE: receiver enable


	USARTx->CR1 |=USART_cfg->Payload_Length ;        // USARTx->CR1 bit 12 M: word length


	USARTx->CR1 |= USART_cfg->parity;				// USARTx->CR1 bit 10 PCE: Parity Control enable bit 9 PS: Parity selection

	USARTx->CR2 |= USART_cfg->StopBit;              // USART_CR2 bits 13:12 STOP: stop bits

    USARTx->CR3 |= USART_cfg->HwFlowCtl ;          // USART_CR3 bit 9 CTSE: CTS enable bit 8 RTSE: RTS enable

    BRR = USART_BRR_Register(pclk , USART_cfg->BaudRate);
    USARTx->BRR = BRR ;

    if(USART_cfg-> IRQ_Enable != USART_IRQ_Enable_NONE )
    {
    	USARTx->CR1 |=(USART_cfg->IRQ_Enable);

    	/* Enable NVIC for USARTx IRQ */
    	if(USARTx == USART1)
    		NVIC_IRQ37_USART1_EN();

    	else if(USARTx == USART2)
    		NVIC_IRQ38_USART2_EN();

    	else if(USARTx == USART3)
    		NVIC_IRQ39_USART3_EN();

    }

}

/*
 * @Fn                -MCAL_USART_DeInit
 * @brief             -DeInitialize USART as Asynchronous only
 * @param [in]        -USARTx: where x can be (1..3 depending on device used)
 * @retval            -none
 * Note               -Reset the model by RCC
 */
void MCAL_USART_DeInit(USART_Typedef * USARTx)
{
  if(USARTx == USART1)
  {
	  RCC_USART1_CLK_DI();
	  NVIC_IRQ37_USART1_DI();
  }
  else if(USARTx == USART2)
  {
	  RCC_USART2_CLK_DI();
	  NVIC_IRQ38_USART2_DI();
  }
  else if(USARTx ==  USART2)
  {
	  RCC_USART3_CLK_DI();
	  NVIC_IRQ39_USART3_DI();
  }
}

void  MCAL_USART_GPIO_Set_Pins(USART_Typedef * USARTx)
{

    GPIO_PinConfig_t pin_config ;
	if(USARTx == USART1)
	{
		   // PA9  TX
		   // PA10 RX
		   // PA11 CTS
		   // PA12 RTS

		pin_config.GPIO_PinNumber = GPIO_PIN_9 ;
		pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &pin_config);

		pin_config.GPIO_PinNumber = GPIO_PIN_10 ;
		pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
		MCAL_GPIO_Init(GPIOA, &pin_config);

		if(Global_USART_config[0]->HwFlowCtl == USART_HwFlowCtl_CTS || Global_USART_config[0]->HwFlowCtl == USART_HwFlowCtl_RTS_CTS )
		{
			pin_config.GPIO_PinNumber = GPIO_PIN_11 ;
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &pin_config);
		}
		if(Global_USART_config[0]->HwFlowCtl == USART_HwFlowCtl_RTS || Global_USART_config[0]->HwFlowCtl == USART_HwFlowCtl_RTS_CTS )
		{
			pin_config.GPIO_PinNumber = GPIO_PIN_12 ;
			pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &pin_config);
		}
	}
	else if (USARTx == USART2)
	{
		// PA2 Tx
		// PA3 Rx
		// PA0 CTS
		// PA1 RTS

		// PA2 Tx
		pin_config.GPIO_PinNumber = GPIO_PIN_2;
		pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pin_config);

		// PA3 Rx
		pin_config.GPIO_PinNumber = GPIO_PIN_3;
		pin_config.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &pin_config);

		if (Global_USART_config[1]->HwFlowCtl == USART_HwFlowCtl_CTS||Global_USART_config[1]->HwFlowCtl==USART_HwFlowCtl_RTS_CTS)
		{
			// PA0 CTS
			pin_config.GPIO_PinNumber = GPIO_PIN_0;
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pin_config);
		}



		if (Global_USART_config[1]->HwFlowCtl == USART_HwFlowCtl_RTS || Global_USART_config[1]->HwFlowCtl == USART_HwFlowCtl_RTS_CTS)
		{
			// PA1 RTS
			pin_config.GPIO_PinNumber = GPIO_PIN_1;
			pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_config);
		}

	}
	else if (USARTx == USART3)
	{
		// PB10 Tx
		// PB11 Rx
		// PA13 CTS
		// PA14 RTS
		// PB10 Tx
		pin_config.GPIO_PinNumber = GPIO_PIN_10;
		pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		pin_config.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pin_config);

		// PB11 Rx
		pin_config.GPIO_PinNumber = GPIO_PIN_11;
		pin_config.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &pin_config);

		if (Global_USART_config[2]->HwFlowCtl == USART_HwFlowCtl_CTS||Global_USART_config[2]->HwFlowCtl==USART_HwFlowCtl_RTS_CTS)
		{
			// PB13 CTS
			pin_config.GPIO_PinNumber = GPIO_PIN_13;
			pin_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pin_config);
		}



		if (Global_USART_config[2]->HwFlowCtl == USART_HwFlowCtl_RTS || Global_USART_config[2]->HwFlowCtl == USART_HwFlowCtl_RTS_CTS)
		{
			// PB14 RTS
			pin_config.GPIO_PinNumber = GPIO_PIN_14;
			pin_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pin_config.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_config);
		}

	}
}

/* ================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- Send buffer on UART
 * @param [in] 		- USARTx where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer buffer
 * @param [in] 		- Polling Enable or disable
 * @retval 			- none
 * Note				- Initialize UART first
 * 					- when transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register)
 * 					- the value written in the MSB ( bit 7 or bit 8 depending on the data length ) has no effect
 * 					- because it is replaced by the parity
 * 					- when receiving with the parity enabled the value read in the MSB bit is the received parity bit
 */
void MCAL_USART_sendData(USART_Typedef * USARTx,uint16_t * pTxBuffer , enum polling_Mechanism pollingEn)
{
	/* 1. Wait until TXE flag is set in the SR */
	if(pollingEn ==  enable)
	{
//		Bit 7 TXE: Transmit data register empty
//		This bit is set by hardware when the content of the TDR register has been transferred into
//		the shift register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It
//		is cleared by a write to the USART_DR register.
//		0: Data is not transferred to the shift register
//		1: Data is transferred to the shift register)
//		Note: This bit is used during single buffer transmission

		while(!(USARTx->SR & 1<<7));

	}

	/* Check the USART_WordLength item for 9-bit or 8-bit in a frame */

	/* When Transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	 * the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	 * because it is replaced by the parity.
	 * When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
	 */

	if(USARTx == USART1)
	{
		if(Global_USART_config[0]->Payload_Length == USART_Payload_Length_8B)
			USARTx->DR = (*pTxBuffer) & (uint8_t)0xFF ;
		else
		    USARTx->DR = (*pTxBuffer) & (uint16_t)0x01FF;
	}
	else if(USARTx == USART2)
	{
		if(Global_USART_config[1]->Payload_Length == USART_Payload_Length_8B)
			USARTx->DR = (*pTxBuffer) & (uint8_t)0xFF ;
		else
		    USARTx->DR = (*pTxBuffer) & (uint16_t)0x01FF;
	}
	else if(USARTx == USART3)
	{
		if(Global_USART_config[2]->Payload_Length == USART_Payload_Length_8B)
			USARTx->DR = (*pTxBuffer) & (uint8_t)0xFF ;
		else
		    USARTx->DR = (*pTxBuffer) & (uint16_t)0x01FF;
	}
}

void MCAL_UART_WAIT_TC(USART_Typedef* USARTx)
{
	/* Wait till TC flag is set in the SR */
	while(!(USARTx->SR & 1<<6));
}

/* @Fn				- MCAL_USART_ReceiveData
* @brief			- receive buffer on UART
* @param [in] 		- USARTx where x can be (1..3 depending on device used)
* @param [in] 		- pRxBuffer buffer
* @param [in] 		- Polling Enable or disable
* @retval 			- none
* Note				- Initialize UART first
* 					- when transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register)
* 					- the value written in the MSB ( bit 7 or bit 8 depending on the data length ) has no effect
* 					- because it is replaced by the parity
* 					- when receiving with the parity enabled the value read in the MSB bit is the received parity bit
*/
void MCAL_USART_ReceiveData(USART_Typedef * USARTx,uint16_t * pRxBuffer , enum polling_Mechanism pollingEn)
{
	/* 1. Wait until RXNE flag is set in the SR */
    if(pollingEn == enable)
  	while(!(USARTx->SR & 1<<5));

    if(USARTx == USART1)
    {
    	/* 8 Bits Data */
    	if(Global_USART_config[0]->Payload_Length == USART_Payload_Length_8B)
    	{
    		if(Global_USART_config[0]->parity == USART_Parity_NONE)
    		{
    			/* Just least byte is data */
    			*pRxBuffer =USARTx->DR & (uint8_t)0xFF ;
    		}
        	else
        	{
        		/* just least 7 bits are data */
        		*pRxBuffer = USARTx->DR & (uint8_t)0x7F ;
        	}
    	}
    	/* 9 Bits Data */
    	else
    	{
			if (Global_USART_config[0]->parity == USART_Parity_NONE)
			{
				/* All 9 bits are data */
				*pRxBuffer = USARTx->DR ;
			}
			else
			{
				/* Just least byte is data */
				*pRxBuffer = USARTx->DR & (uint8_t)0xFF ;
			}

    	}
    }
    else  if(USARTx == USART2)
    {
    	/* 8 Bits Data */
    	if(Global_USART_config[1]->Payload_Length == USART_Payload_Length_8B)
    	{
    		if(Global_USART_config[1]->parity == USART_Parity_NONE)
    		{
    			/* Just least byte is data */
    			*pRxBuffer =USARTx->DR & (uint8_t)0xFF ;
    		}
        	else
        	{
        		/* just least 7 bits are data */
        		*pRxBuffer = USARTx->DR & (uint8_t)0x7F ;
        	}
    	}
    	/* 9 Bits Data */
    	else
    	{
			if (Global_USART_config[1]->parity == USART_Parity_NONE)
			{
				/* All 9 bits are data */
				*pRxBuffer = USARTx->DR ;
			}
			else
			{
				/* Just least byte is data */
				*pRxBuffer = USARTx->DR & (uint8_t)0xFF ;
			}

    	}
    }
    else  if(USARTx == USART3)
    {
    	/* 8 Bits Data */
    	if(Global_USART_config[2]->Payload_Length == USART_Payload_Length_8B)
    	{
    		if(Global_USART_config[2]->parity == USART_Parity_NONE)
    		{
    			/* Just least byte is data */
    			*pRxBuffer =USARTx->DR & (uint8_t)0xFF ;
    		}
        	else
        	{
        		/* just least 7 bits are data */
        		*pRxBuffer = USARTx->DR & (uint8_t)0x7F ;
        	}
    	}
    	/* 9 Bits Data */
    	else
    	{
			if (Global_USART_config[2]->parity == USART_Parity_NONE)
			{
				/* All 9 bits are data */
				*pRxBuffer = USARTx->DR ;
			}
			else
			{
				/* Just least byte is data */
				*pRxBuffer = USARTx->DR & (uint8_t)0xFF ;
			}

    	}
    }
}

void USART1_IRQHandler (void)
{
	Global_USART_config[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	Global_USART_config[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler (void)
{
	Global_USART_config[2]->P_IRQ_CallBack();
}
