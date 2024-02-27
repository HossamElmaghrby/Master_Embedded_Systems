/*
 * stm32F103x6_SPI_Driver.c
 *
 *  Created on: Feb 22, 2024
 *      Author: Elmag
 */


//Include

#include "stm32F103x6_SPI_Driver.h"

//========Generic Variables====================
SPI_Config *G_SPI_Config[2] = {NULL , NULL};


/* ================================================================ */
/* ======================= Generic Macros ========================= */
/* ================================================================ */

#define SPI1_Index     0
#define SPI2_Index     1

#define SPI_SR_TXE		(uint16_t)(1<<1)
#define SPI_SR_RXNE		(uint16_t)(1<<0)

/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

/* ================================================================
 * @Fn 				- MCAL_SPI_Init
 * @brief 			- Initializes SPIx according to the specified parameters in SPI_Config_t
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- Config : a pointer to SPI_Config_t structure that contains the configuration information for the specified SPI Module
 * @retval 			- None
 * Note 			- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 * 					- You have to configure RCC to select clock for the selected SPI Module
 */

void MCAL_SPI_Init(SPI_Typedef *SPIx , SPI_Config *cfg)
{
	if(SPIx == SPI1)
	{
		G_SPI_Config[SPI1_Index] = cfg ;

		//open RCC clock
		RCC_SPI1_CLK_EN();

		//open interrupt request for spi1
		NVIC_IRQ35_SPI1_EN();

	}
	else if(SPIx == SPI2)
	{
		G_SPI_Config[SPI2_Index]= cfg ;

		//open RCC clock
		RCC_SPI2_CLK_EN();

		//open interrupt request for spi2
		NVIC_IRQ36_SPI2_EN();
	}

	//select mode master or slave
	SPIx->SPI_CR1 |= cfg->Device_Mode ;

	//select communication mode
	SPIx->SPI_CR1 |= cfg->Communication_Mode ;

	//select data size
	SPIx->SPI_CR1 |= cfg->Data_Size ;

	//select data order
	SPIx->SPI_CR1 |= cfg->Data_Order ;

	//select baud rate
	SPIx->SPI_CR1 |= cfg->Baud_Rate ;

	//select clock polarity
	SPIx->SPI_CR1 |= cfg->CLK_Polarity ;

	//select clock phase
	SPIx->SPI_CR1 |= cfg->CLK_Phase ;

	if((cfg->NSS == SPI_NSS_HW_Slave) | (cfg->NSS == SPI_NSS_HW_Master_Output_enable) |(cfg->NSS == SPI_NSS_HW_multiMaster_enable))
	{
		SPIx->SPI_CR2 |= cfg->NSS ;
	}
	else if((cfg->NSS == SPI_NSS_SW_Reset)|( cfg->NSS == SPI_NSS_SW_Set))
	{
		SPIx->SPI_CR1 |= cfg->NSS ;
	}

	//interrupt enable
	SPIx->SPI_CR2 |=cfg->IRQ_Enable ;


	//Enable the SPI
	SPIx->SPI_CR1 |= (uint16_t)(1<<6) ;
}
/* ================================================================
 * @Fn 				- MCAL_SPI_DeInit
 * @brief 			- Resets Selected SPI Module
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_SPI_DeInit(SPI_Typedef *SPIx)
{
	SPIx->SPI_CR1    = 0x0000 ;
	SPIx->SPI_CR2    = 0x0000 ;
	SPIx->SPI_SR     = 0x0002 ;
	SPIx->SPI_DR     = 0x0000 ;
	SPIx->SPI_CRCPR  = 0x0007 ;
	SPIx->SPI_RXCRCR = 0x0000 ;
	SPIx->SPI_TXCRCR = 0x0000 ;
	SPIx->SPI_I2SCFGR= 0x0000 ;
	SPIx->SPI_I2SPR  = 0x0002 ;

	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_DI();
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ35_SPI2_DI();
		RCC_SPI2_CLK_EN();
	}
}
/* ================================================================
 * @Fn 				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Must open clock for AFIO & GPIO After GPIO Initialization
 * 					- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_Typedef *SPIx)
{
	GPIO_PinConfig_t SPI_GPIO_cfg ;
	if(SPIx == SPI1)
	{
		//PA4  SPI1_NSS
		//PA5  SPI1_SCK
		//PA6  SPI1_MISO
		//PA7  SPI1_MOSI

		//Master
		if(G_SPI_Config[SPI1_Index]->Device_Mode == SPI_Mode_Master)
		{
			//PA4  SPI1_NSS
			switch(G_SPI_Config[SPI1_Index]->NSS)
			{
			//output
			case SPI_NSS_HW_Master_Output_enable:
				/* Hardware Master/NNS Output Alternate function push-pull */
				SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_4 ;
		    	SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
				SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
				break ;
			//input
			case SPI_NSS_HW_multiMaster_enable:
				/* Hardware Master/Slave Input Floating */
				SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_4 ;
		    	SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
				break;
			}
			//PA5  SPI1_SCK
			// Master Alternate function push-pull
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_5 ;
			SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_AF_PP ;
			SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);

			//PA6  SPI1_MISO
			//Full duplex / master Input floating / Input pull-up
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);

			//PA7  SPI1_MOSI
			//Full duplex / master Alternate function push-pull
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_7 ;
			SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_AF_PP ;
			SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
		}
		//Slave
		else
		{
			/* PA4 : SPI1_NSS */
			if(G_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HW_Slave)
			{
				/* Hardware Master/Slave Input Floating */
				SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_4;
				SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
			}

			/* PA5 : SPI1_SCK */
			/* Slave Input floating */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_5;
			SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);

			/* PA6 : SPI1_MISO */
			/* Full duplex / slave (point to point) Alternate function push-pull */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);

			/* PA7 : SPI1_MOSI */
			/* Full duplex / slave Input floating / Input pull-up */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_7;
			SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
		}
	}
	else if (SPIx == SPI2)
	{
		//PB12  SPI1_NSS
		//PBI13 SPI1_SCK
		//PAB14 SPI1_MISO
		//PBI15 SPI1_MOSI
		//PA4  SPI1_NSS
		switch(G_SPI_Config[SPI1_Index]->NSS)
		{
		//output
		case SPI_NSS_HW_Master_Output_enable:
			/* Hardware Master/NNS Output Alternate function push-pull */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_12 ;
	    	SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
			break ;
		//input
		case SPI_NSS_HW_multiMaster_enable:
			/* Hardware Master/Slave Input Floating */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_12 ;
	    	SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);
			break;
		}
		//PBI13 SPI1_SCK
		// Master Alternate function push-pull
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_13 ;
		SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_AF_PP ;
		SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);

		//PAB14 SPI1_MISO
		//Full duplex / master Input floating / Input pull-up
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_14;
		SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);

		//PBI15 SPI1_MOSI
		//Full duplex / master Alternate function push-pull
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_15 ;
		SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_AF_PP ;
		SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);
	}
	//Slave
	else
	{
		//PB12  SPI1_NSS
		if(G_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HW_Slave)
		{
			/* Hardware Master/Slave Input Floating */
			SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_12;
			SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);
		}

		//PBI13 SPI1_SCK
		/* Slave Input floating */
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_13;
		SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &SPI_GPIO_cfg);

		//PAB14 SPI1_MISO
		/* Full duplex / slave (point to point) Alternate function push-pull */
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_14;
		SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		SPI_GPIO_cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);

		//PBI15 SPI1_MOSI
		/* Full duplex / slave Input floating / Input pull-up */
		SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_15;
		SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA, &SPI_GPIO_cfg);
	}
}

/* ================================================================
 * @Fn 				- MCAL_SPI_Send_Data
 * @brief 			- Send Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer Which holds the Tx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_SPI_Send_Data(SPI_Typedef *SPIx , uint16_t *pTxBuffer ,enum Polling_Mechanism polling_En)
{
	if(polling_En == SPI_enable)
 	  while(!(SPIx->SPI_SR &SPI_SR_TXE));

	SPIx->SPI_DR = *(pTxBuffer);
}

/* ================================================================
 * @Fn 				- MCAL_SPI_Recieve_Data
 * @brief 			- Receive Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pRxBuffer : Pointer to buffer which holds Rx data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_Recieve_Data(SPI_Typedef *SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == SPI_enable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*(pRxBuffer) = SPIx->SPI_DR ;
}

/* ================================================================
 * @Fn 				- MCAL_SPI_TX_RX
 * @brief 			- Transmit and Receive Data
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer which holds Transmit and Received data
 * @param [in] 		- Polling_En : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_TX_RX(SPI_Typedef *SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == SPI_enable)
		while(!(SPIx->SPI_SR & SPI_SR_TXE));

	SPIx->SPI_DR = *(pTxBuffer);

	if(Polling_En == SPI_enable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*(pTxBuffer) = SPIx->SPI_DR ;
}

void SPI1_IRQHandler()
{
	struct S_IRQ_SRC irq_scr ;

	irq_scr.TXEIE  = (((SPI1->SPI_SR)>>1) & 0x1);
	irq_scr.RXNEIE = (((SPI1->SPI_SR)>>0) & 0x1);
	irq_scr.ERRIE  = (((SPI1->SPI_SR)>>4) & 0x1);

	G_SPI_Config[SPI1_Index]->P_IRQ_CallBack(irq_scr) ;
}

void SPI2_IRQHandler()
{
	struct S_IRQ_SRC irq_scr ;

	irq_scr.TXEIE  = (((SPI2->SPI_SR)>>1) & 0x1);
	irq_scr.RXNEIE = (((SPI2->SPI_SR)>>0) & 0x1);
	irq_scr.ERRIE  = (((SPI2->SPI_SR)>>4) & 0x1);

	G_SPI_Config[SPI1_Index]->P_IRQ_CallBack(irq_scr) ;
}
