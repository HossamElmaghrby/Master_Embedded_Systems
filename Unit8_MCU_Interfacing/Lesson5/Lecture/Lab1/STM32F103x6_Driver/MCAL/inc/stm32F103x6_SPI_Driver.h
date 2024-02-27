/*
 * stm32F103x6_SPI_Driver.h
 *
 *  Created on: Feb 22, 2024
 *      Author: Elmag
 */

#ifndef INC_STM32F103X6_SPI_DRIVER_H_
#define INC_STM32F103X6_SPI_DRIVER_H_

#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_Driver.h"


/* ================================================================ */
/* ============= User type definitions (structures) =============== */
/* ================================================================ */

struct S_IRQ_SRC
{
	uint8_t TXEIE:1 ;    // TX empty interrupt
	uint8_t RXNEIE:1 ;   // RX not empty interrupt
	uint8_t ERRIE:1 ;   //Error interrupt
	uint8_t reserved:5 ;
};


typedef struct
{
	uint16_t Device_Mode ;           //this parameter specific SPI master or slave mode
	                                 //set based on @ref_SPI_Device_Mode

	uint16_t Communication_Mode ;   //this parameter specific SPI  2_line or 1_line and bidirectional or unidirectional
	                                //set based on @ref_SPI_Communiction_Mode

	uint16_t Data_Size ;            //this parameter specific SPI Frame format 8bit or 16bit se
	                                //set based on @ref_SPI_Data_Size

	uint16_t Data_Order ;           //this parameter specific SPI order LSB OR MSB
	                                //set based on @ref_SPI_Data_Order

	uint16_t Baud_Rate ;            //this parameter specific SPI Baud Rate Fclk/2 max not need in slave mode
	                                // set based on @ref_SPI_Baud_Rate

	uint16_t CLK_Polarity ;        //this parameter specific SPI polarity idle high or idle low
	                               //set based on @ref_SPI_CLK_Polarity

	uint16_t CLK_Phase ;           //this parameter specific SPI Phase first edge or second edge
	                               //set based on @ref_SPI_CLK_Phase

	uint16_t NSS ;                 //this parameter specific SPI hardware or software
	                               //set based on  @ref_SPI_NSS

	uint16_t IRQ_Enable ;            //this parameter specific SPI Interrupt request enable
	                               //set based on @ref_SPI_IRQ_Enable

	void (*P_IRQ_CallBack)(struct S_IRQ_SRC);    //c function   callBack when interrupt happen
}SPI_Config;

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */

//@ref_SPI_Device_Mode
// CR1.Bit 2 MSTR: Master selection
//0: Slave configuration
//1: Master configuration

#define SPI_Mode_Master                  (uint16_t)(1<<2)
#define SPI_Mode_slave                   (uint16_t)(0)


//@ref_SPI_Communiction_Mode
//CR1 Register
#define SPI_Communication_Mode_2line_Full_duplex      (uint16_t)(0)
#define SPI_Communication_Mode_2line_receive_only     (uint16_t)(1<<10)

#define SPI_Communication_Mode_1line_receive_only     (uint16_t)(1<<15)
#define SPI_Communication_Mode_1line_Transmit_only    (uint16_t)(1<<15|1<<14)


//@ref_SPI_Data_Size
//CR1.Bit 11 DFF: Data frame format
//0: 8-bit data frame format is selected for transmission/reception
//1: 16-bit data frame format is selected for transmission/reception
#define SPI_Data_Size_8bit                            (uint16_t)(0)
#define SPI_Data_Size_16bit                           (uint16_t)(1<<11)


//@ref_SPI_Data_Order
//CR1.Bit 7 LSBFIRST: Frame format
//0: MSB transmitted first
//1: LSB transmitted first
#define SPI_Data_Order_MSB_First                     (uint16_t)(0)
#define SPI_Data_Order_LSB_First                     (uint16_t)(1<<7)

//@ref_SPI_Baud_Rate
//CR1.Bits 5:3 BR[2:0]: Baud rate control
//000: fPCLK/2
//001: fPCLK/4
//010: fPCLK/8
//011: fPCLK/16
//100: fPCLK/32
//101: fPCLK/64
//110: fPCLK/128
//111: fPCLK/256
#define SPI_BaudRate_Prescaler_2                      (uint16_t)(0)
#define SPI_BaudRate_Prescaler_4                      (uint16_t)(0b001<<3)
#define SPI_BaudRate_Prescaler_8                      (uint16_t)(0b010<<3)
#define SPI_BaudRate_Prescaler_16                     (uint16_t)(0b011<<3)
#define SPI_BaudRate_Prescaler_32                     (uint16_t)(0b100<<3)
#define SPI_BaudRate_Prescaler_64                     (uint16_t)(0b101<<3)
#define SPI_BaudRate_Prescaler_128                    (uint16_t)(0b110<<3)
#define SPI_BaudRate_Prescaler_256                    (uint16_t)(0b111<<3)


// @ref_SPI_CLK_Polarity
//CR1.Bit1 CPOL: Clock polarity
//0: CK to 0 when idle
//1: CK to 1 when idle
#define SPI_CLK_Polarity_LOW_idle                     (uint16_t)(0)
#define SPI_CLK_Polarity_HIGH_idle                    (uint16_t)(1<<1)

//@ref_SPI_CLK_Phase
//CR1.Bit 0 CPHA: Clock phase
//0: The first clock transition is the first data capture edge
//1: The second clock transition is the first data capture edge
#define SPI_CLK_Phase_first_edge                     (uint16_t)(0)
#define SPI_CLK_Phase_second_edge                    (uint16_t)(1<<0)

//@ref_SPI_NSS
//• Hardware NSS management (SSM = 0)
//Two configurations are possible depending on the NSS output configuration (SSOE bit
//in register SPI_CR2).
//– NSS output enabled (SSM = 0, SSOE = 1)
//This configuration is used only when the device operates in master mode. The
//NSS signal is driven low when the master starts the communication and is kept
//low until the SPI is disabled.
//– NSS output disabled (SSM = 0, SSOE = 0)
//This configuration allows multimaster capability for devices operating in master
//mode. For devices set as slave, the NSS pin acts as a classical NSS input: the
//slave is selected when NSS is low and deselected when NSS high.
#define SPI_NSS_HW_Slave                           (uint16_t)(0)
#define SPI_NSS_HW_Master_Output_enable            (uint16_t)(1<<2)
#define SPI_NSS_HW_multiMaster_enable              (uint16_t)(0)

//• Software NSS management (SSM = 1)
//The slave select information is driven internally by the value of the SSI bit in the
//SPI_CR1 register. The external NSS pin remains free for other application uses.
#define SPI_NSS_SW_Set                             (uint16_t)((1<<9)|(1<<8))
#define SPI_NSS_SW_Reset                           (uint16_t) (1<<9)

//@ref_SPI_IRQ_Enable
//CR2
#define SPI_IRQ_ENABLE_NONE							(uint16_t) (0)			// IRQ Disable
#define SPI_IRQ_ENABLE_TXEIE						(uint16_t) (1<<7)		// TX buffer empty interrupt enable
#define SPI_IRQ_ENABLE_RXNEIE						(uint16_t) (1<<6)		// RX buffer not empty interrupt enable
#define SPI_IRQ_ENABLE_ERRIE						(uint16_t) (1<<5)

enum Polling_Mechanism
{
	SPI_disable,
	SPI_enable
};
/* ================================================================ */
/* =========== APIs Supported by "MCAL SPI DRIVER" ================ */
/* ================================================================ */

void MCAL_SPI_Init(SPI_Typedef *SPIx , SPI_Config *cfg);
void MCAL_SPI_DeInit(SPI_Typedef *SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_Typedef *SPIx);

void MCAL_SPI_Send_Data(SPI_Typedef *SPIx , uint16_t *pTxBuffer ,enum Polling_Mechanism polling_En);
void MCAL_SPI_Recieve_Data(SPI_Typedef *SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En);

void MCAL_SPI_TX_RX(SPI_Typedef *SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);

#endif /* INC_STM32F103X6_SPI_DRIVER_H_ */
