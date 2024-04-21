/*
 * Atmega32_SPI_Driver.c
 *
 * Created: 2/28/2024 9:46:50 AM
 *  Author: Elmag
 */ 

#include "Atmega32_SPI_Driver.h"
 SPI_Config *G_SPI_Config = NULL ;
void MCAL_SPI_Init(SPI_TypeDef_t *SPIx , SPI_Config *cfg)
{
	G_SPI_Config = cfg ;
	
	if(cfg->CLK_Speed == SPI_CLK_Speed_Double)
	{
		SPIx->_SPCR |= cfg->Baud_Rate ;
		SPIx->_SPSR |=(1<<0) ;
	}
	else
	{
		SPIx->_SPCR |= cfg->Baud_Rate ;
	}
	
	SPIx->_SPCR |= cfg->CLK_Phase ;
	
	SPIx->_SPCR |= cfg->CLK_Polarity ;
	
	SPIx->_SPCR |= cfg->Data_Order ;
	
	SPIx->_SPCR |= cfg->Device_Mode ;
	
	if(cfg->IRQ_Enable != SPI_IR_Enable_NONE)
	{
		//Enable global interrupt
		Enable_Global_Interrupt();
		
		SPIx->_SPCR |= cfg->IRQ_Enable ;
	}
	
	//enable SPI
	SPIx->_SPCR |= (1<<6);
}
void MCAL_SPI_DeInit(SPI_TypeDef_t *SPIx)
{
	SPIx->_SPCR = 0x00;
	SPIx->_SPSR &=~(1<<0);
	Disable_Global_Interrupt();
}

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef_t *SPIx)
{
	//PB4  SPI1_SS
	//PB5  SPI1_MOSI
	//PB6  SPI1_MISO
	//PB7  SPI1_SCK
	GPIO_PinConfig_t SPI_GPIO_cfg ;
	//Master
  if(G_SPI_Config->Device_Mode == SPI_Mode_Master)
   {
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_4 ;
	   SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);
	   
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_5 ;
	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);
	   
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_6 ;
	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_INPUT_FLO ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);
	   
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_7 ;
  	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
  	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);	   
   }
   //Slave
   else
   {
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_4 ;
  	   SPI_GPIO_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ; 
  	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);
		 
	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_5 ;
	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_INPUT_FLO ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);

	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_6 ;
	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_OUTPUT_PP ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);	  

	   SPI_GPIO_cfg.GPIO_PinNumber = GPIO_PIN_7 ;
	   SPI_GPIO_cfg.GPIO_MODE =GPIO_MODE_INPUT_FLO ;
	   MCAL_GPIO_Init(GPIOB ,&SPI_GPIO_cfg);   		 
   }
}

void MCAL_SPI_Send_Data(SPI_TypeDef_t *SPIx , uint16_t *pTxBuffer ,enum Polling_Mechanism polling_En)
{
	SPIx->_SPDR = *pTxBuffer ;
	
	if(polling_En == SPI_enable)
	    while(!(SPIx->_SPSR & (1<<7)));
}
void MCAL_SPI_Recieve_Data(SPI_TypeDef_t *SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En)
{
		if(Polling_En == SPI_enable)
		  while(!(SPIx->_SPSR & (1<<7)));
		  
		  *pRxBuffer = SPIx->_SPDR ;
}

void MCAL_SPI_TX_RX(SPI_TypeDef_t *SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
		SPIx->_SPDR = *pTxBuffer ;
		
		if(Polling_En == SPI_enable)
		while(!(SPIx->_SPSR & (1<<7)));
		
		
		if(Polling_En == SPI_enable)
		while(!(SPIx->_SPSR & (1<<7)));
		
		*pTxBuffer = SPIx->_SPDR ;		
			
}

//================IRQ Function Definitions===============
ISR(SPI_STC_vect)
{
	G_SPI_Config->P_IRQ_CallBack();
}