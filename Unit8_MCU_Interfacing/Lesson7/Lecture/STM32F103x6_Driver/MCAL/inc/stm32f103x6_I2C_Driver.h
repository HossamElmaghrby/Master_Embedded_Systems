/*
 * stm32f103x6_I2C_Driver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Elmag
 */

#ifndef INC_STM32F103X6_I2C_DRIVER_H_
#define INC_STM32F103X6_I2C_DRIVER_H_

#include "stm32f103x6_I2C_Driver.h"
#include "stm32f103x6_GPIO_Driver.h"
#include "stm32f103x6_RCC_Driver.h"
/* ================================================================ */
/* ========================= Structures =========================== */
/* ================================================================ */
typedef struct
{
	uint8_t	    Enable_Dual_Address;		  	//Enable : 1, Disable	: 0
	uint8_t		Slave_First_Address;
	uint8_t		Slave_Second_Address;
	uint16_t    Slave_Address_Mode;			   	// This parameter must be set based on @ref I2C_SLAVE_ADDRESS_MODE_DEFINE
}I2C_slave_address_t;

typedef enum
{
	I2C_EV_STOP,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ,					// APP_Layer should send data (I2C slave send data)
	I2C_EV_DATA_RCV						// APP_Layer should receive data (I2C slave receive data)
}Slave_State;
typedef struct
{
   uint32_t Clock_Frequency ;                //Specifies I2C Clock Frequency
                                             //set based on @ref I2C_Clock_Speed_Define

   uint8_t Clock_Stretching ;               // specifies enable or disable clock stretching  in slave mode only
                                            // set based on @ref  I2C_Clock_Stretch_Define

   uint8_t General_Call ;                   //set based on @ref I2C_General_Call_Define

   uint16_t Master_Mode ;                    //specifies  Master mode selection SM OR FM
                                            //set based on @ref I2C_Master_Mode_Define

   uint8_t Mode ;                            //specifies SMBus mode or I2C mode
    										 // set based on @ref I2C_Mode_Defien

   uint16_t ACK_Control ;                     //specifies Enable or disable Acknowledge
   	    	   	   	   	   	   	   	   	   	   	 // set based on @ref I2C_ACK_Control_Defien

   I2C_slave_address_t		Slave_Address;		// Slave address information from user

   void (*p_slave_CallBack)(Slave_State state);  // Set the C Function which will be called once IRQ Happens

}I2C_Config;

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */

//@ref I2C_Clock_Speed_Define
/* Standard Speed (up to 100 kHz)
 * Fast Speed (up to 400 kHz)
 * to configure clock before enable the peripheral
 * I2C_CR2 -> Bits 5:0 FREQ[5:0]: Peripheral clock frequency
 * • Configure the clock control registers
 *     T_high = CCR * Tpclk1
 * • Configure the rise time register
 */
#define I2C_Clock_Frequency_SM_50KHZ                  (50000U)
#define I2C_Clock_Frequency_SM_100KHZ                 (100000U)
#define I2C_Clock_Frequency_FM_200KHZ                 (200000U) // NOT Supported
#define I2C_Clock_Frequency_FM_400KHZ                 (400000U) // NOT Supported

//@ref  I2C_Clock_Stretch_Define

//I2C_CR1 . Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
//it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled

#define I2C_Clock_Stretch_Enable                 (uint8_t)(0)
#define I2C_Clock_Stretch_Disable                (uint8_t)(I2C_CR1_NOSTRETCH)


//@ref I2C_General_Call_Define
//I2C_CR1 .Bit 6 ENGC: General call enable
//  0: General call disabled. Address 00h is NACKed.
//  1: General call enabled. Address 00h is ACKed

#define I2C_General_Call_Enable                   (uint8_t)(I2C_CR1_ENGC)
#define I2C_General_Call_Disable                  (uint8_t)(0)

// @ref I2C_Master_Mode_Define
// I2C_CCR .Bit 15 F/S: I2C master mode selection
//0: Sm mode I2C
//1: Fm mode I2C

#define I2C_Master_Mode_SM                          (uint16_t)(0)
#define I2C_Master_Mode_FM                          (uint16_t)(1<<15)

//@ref I2C_Mode_Defien
//I2C_CR1 .Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode

#define I2C_Mode_I2C_Mode                             (uint8_t)(0)
#define I2C_Mode_SMBUS_Mode                           (uint8_t)(I2C_CR1_SMBUS)

//@ref I2C_ACK_Control_Defien
//I2C_CR1 .Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)

#define I2C_ACK_Control_Enable                       (uint16_t)(I2C_CR1_ACK)
#define I2C_ACK_Control_Disable						 (uint16_t)(0)

//@ref I2C_SLAVE_ADDRESS_MODE_DEFINE
/* I2C_OAR1
 * Bit 15 ADDMODE Addressing mode (slave mode)
 * 0: 7-bit slave address (10-bit address not acknowledged)
 * 1: 10-bit slave address (7-bit address not acknowledged)
 */
#define I2C_SLAVE_ADDRESS_MODE_7_BIT		      	(uint16_t)(0)
#define I2C_SLAVE_ADDRESS_MODE_10_BIT		    	(uint16_t)(1<<15)


//===========================Enum Functions============

typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	Repeated_Start
}Start_Condition;

typedef enum
{
	Reset,
	Set
}I2C_FlagStatus;

typedef enum
{
	Bus_Busy,
	EV5,
	EV6,
	EV7_1,
	EV7,
	EV8_1,
	EV8,
	Master_Transmitter_Event = ((uint32_t)(0x00070080))		// Check if BUSY ,TRA ,MSL W,TXE flags are all set
}Status;

typedef enum
{
	Disable,
	Enable
}Functional_State;

typedef enum
{
	Transmitter,
	Receiver
}I2C_Direction;

/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

void MCAL_I2C_Init(I2C_Typedef *I2Cx , I2C_Config *I2C_cfg);
void MCAL_I2C_DInit(I2C_Typedef *I2Cx );

void MCAL_I2C_GPIO_Set_Pin(I2C_Typedef *I2Cx);

//Master polling Mechanism
void MCAL_I2C_Master_Tx(I2C_Typedef *I2Cx , uint8_t Dev_Address ,uint8_t *Data_Out , uint8_t Data_Length ,Stop_Condition Stop , Start_Condition Start );
void MCAL_I2C_Master_Rx(I2C_Typedef *I2Cx , uint8_t Dev_Address ,uint8_t *Data_in , uint8_t Data_Length ,Stop_Condition Stop , Start_Condition Start );


// Slave Interrupt Mechanism
void MCAL_I2C_Slave_TX(I2C_Typedef *I2Cx, uint8_t data);
uint8_t MCAL_I2C_Slave_RX(I2C_Typedef  *I2Cx);

/* ================================================================ */
/* ======================== Generic APIs ========================== */
/* ================================================================ */


void I2C_Generate_Start(I2C_Typedef *I2Cx ,Functional_State NewState , Start_Condition Start);
void I2C_Send_Address(I2C_Typedef *I2Cx , uint8_t Dev_Address , I2C_Direction Direction);
void I2C_Generate_Stop(I2C_Typedef *I2Cx ,Functional_State NewState);
void I2C_ACKConfig(I2C_Typedef *I2Cx, Functional_State State);
I2C_FlagStatus I2C_Get_FlagStatus(I2C_Typedef *I2Cx ,Status Flag );

#endif /* INC_STM32F103X6_I2C_DRIVER_H_ */
