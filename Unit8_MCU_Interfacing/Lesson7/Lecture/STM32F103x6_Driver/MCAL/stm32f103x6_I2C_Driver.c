/*
 * stm32f103x6_I2C_Driver.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Elmag
 */

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_I2C_Driver.h"

/* ================================================================ */
/* ===================== Generic Variables ======================== */
/* ================================================================ */

I2C_Config G_I2C_Config[2] = {0};

/* ================================================================ */
/* ======================= Generic Macros ========================= */
/* ================================================================ */

#define I2C1_Index				0
#define I2C2_Index				1

/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

/* ================================================================
 * @Fn 				- MCAL_I2C_Init
 * @brief 			- Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- I2C_Config : a pointer to I2C_Config_t structure that contains the configuration information for the specified I2C Module
 * @retval 			- None
 * Note 			- Supported for I2C SM mode only
 * 					- Support only 7-bit address mode
 */

void MCAL_I2C_Init(I2C_Typedef *I2Cx , I2C_Config *I2C_cfg)
{

	uint32_t Pclk1 = 0;
	uint8_t Freq_Range =0 ;
	if(I2Cx == I2C1)
	{
		//PUT the configuration in Global config To use in file
		G_I2C_Config[I2C1_Index] = *I2C_cfg ;

		//enable the clock of I2C1
		RCC_I2C1_CLK_EN() ;
	}
	else if (I2Cx == I2C2)
	{
		//PUT the configuration in Global config To use in file
		G_I2C_Config[I2C2_Index] = *I2C_cfg ;

		//enable the clock of I2C2
		RCC_I2C2_CLK_EN() ;
	}

	if(I2C_cfg->Mode == I2C_Mode_I2C_Mode)
	{
		/* =================== Initialize Timing ==================== */

		//Get pclk1 APB1 frequency value
		Pclk1 = MCAL_RCC_GetPCLK1Freq() ;

		//I2C_CR2 -> Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		//Divided in 1MHZ to be 1 --> 50 in binary

		Freq_Range = (uint8_t)((Pclk1/1000000)<<I2C_CR2_FREQ_Pos);
		I2Cx->I2C_CR2 |= Freq_Range ;

		/* ========= Configure "I2C_CCR" Clock control register ========= */

		//configure the speed in standard mode
		if(I2C_cfg->Master_Mode == I2C_Master_Mode_SM )
		{
			//RCC calculation
			/*
			 * Tclk / 2 = CCR * Tpclk1
			 * CCR = Tclk / (2 * Tpclk1)
			 * CCR = Fpclk / (2 * I2C_ClockFrequency)
			 */

			I2Cx->I2C_CCR = (uint16_t)(Pclk1 /(I2C_cfg->Clock_Frequency << 1));

			/* ========= Configure "I2C_TRISE" Rise time register ============ */
			/*
			 * For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			 * If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			 * therefore the TRISE[5:0] bits must be programmed with 09h.
			 * (1000 ns / 125 ns = 8 + 1)
			 */

			I2Cx->I2C_TRISE = Freq_Range +1 ;
		}
		else if(I2C_cfg->Master_Mode == I2C_Master_Mode_FM)
		{
			//not supported fast mode
		}

		/* ========= Configure "I2C_CR1" Control register 1 ========= */

		//set acknowledge and general call and mode and stretch
		I2Cx->I2C_CR1 |=(uint16_t)(I2C_cfg->ACK_Control | I2C_cfg->General_Call | I2C_cfg->Mode | I2C_cfg->Clock_Stretching) ;

		/* ========= Configure "I2C_OAR" Own address registers ========= */

		//set the first address of slave
		I2Cx->I2C_OAR1 |=(uint16_t)(I2C_cfg->Slave_Address.Slave_First_Address << 1);

		if(I2C_cfg->Slave_Address.Enable_Dual_Address == 1)
		{
			/*
			 * Bits 7:1 ADD2[7:1]: Interface address
			 * 		bits 7:1 of address in dual addressing mode
			 */
			//set the second address of slave
			I2Cx->I2C_OAR2 |=(uint16_t)(I2C_cfg->Slave_Address.Slave_Second_Address << I2C_OAR2_ADD2_Pos);
		}

	}
	else
	{
		//not supported SMBus mode
	}

	if(I2C_cfg->p_slave_CallBack != NULL)
	{
		/* 1. Enable IRQ */
		I2Cx->I2C_CR2 |= (I2C_CR2_ITERREN); // Error interrupt enable
		I2Cx->I2C_CR2 |= (I2C_CR2_ITEVTEN); // Event interrupt enable
		I2Cx->I2C_CR2 |= (I2C_CR2_ITBUFEN); // Buffer interrupt enable
	}

	/* 2. Enable IRQ in NVIC */
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_EN();
		NVIC_IRQ32_I2C1_ER_EN();
	}
	else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_EN();
		NVIC_IRQ34_I2C2_ER_EN();
	}
	//Enable the selected I2C peripheral
	I2Cx->I2C_CR1 |= I2C_CR1_PE ;

}
/* ================================================================
 * @Fn 				- MCAL_I2C_DeInit
 * @brief 			- Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_I2C_DInit(I2C_Typedef *I2Cx )
{
	I2Cx->I2C_CCR  = 0x0000 ;
	I2Cx->I2C_CR1  = 0x0000 ;
	I2Cx->I2C_CR2  = 0x0000 ;
	I2Cx->I2C_DR   = 0x0000 ;
	I2Cx->I2C_OAR1 = 0x0000 ;
	I2Cx->I2C_OAR2 = 0x0000 ;
	I2Cx->I2C_SR1  = 0x0000 ;
	I2Cx->I2C_SR2  = 0x0000 ;
	I2Cx->I2C_TRISE= 0x0002 ;

	if (I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_DI();
		NVIC_IRQ32_I2C1_ER_DI();
		RCC_I2C1_CLK_DI();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_DI();
		NVIC_IRQ34_I2C2_ER_DI();
		RCC_I2C2_CLK_DI();
	}
}

/*================================================================================
 * @Fn 			- MCAL_I2C_GPIO_Set_Pin
 * @brief 			- Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			    - Must open clock for AFIO & GPIO After GPIO Initialization
 * 					- Supported for I2C SM MODE only
 */
void MCAL_I2C_GPIO_Set_Pin(I2C_Typedef *I2Cx)
{
	GPIO_PinConfig_t I2C_GPIO_Cfg ;

	if(I2Cx == I2C1)
	{
		//PB6 : I2C1_SCL
		I2C_GPIO_Cfg.GPIO_PinNumber = GPIO_PIN_6 ;
		I2C_GPIO_Cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		I2C_GPIO_Cfg.GPIO_Output_Speed =GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &I2C_GPIO_Cfg);

		//PB7 : I2C1_SDA
		I2C_GPIO_Cfg.GPIO_PinNumber = GPIO_PIN_7 ;
		I2C_GPIO_Cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		I2C_GPIO_Cfg.GPIO_Output_Speed =GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &I2C_GPIO_Cfg);
	}
	else if(I2Cx ==  I2C2)
	{
		//PB10 : I2C2_SCL
		I2C_GPIO_Cfg.GPIO_PinNumber = GPIO_PIN_10 ;
		I2C_GPIO_Cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		I2C_GPIO_Cfg.GPIO_Output_Speed =GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &I2C_GPIO_Cfg);

		//PB11 : I2C2_SDA
		I2C_GPIO_Cfg.GPIO_PinNumber = GPIO_PIN_11 ;
		I2C_GPIO_Cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD ;
		I2C_GPIO_Cfg.GPIO_Output_Speed =GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &I2C_GPIO_Cfg);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- Dev_Address : slave address
 * @param [in] 		- Data_Out : a pointer to the data which will be send
 * @param [in] 		- Data_Length : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_Tx(I2C_Typedef *I2Cx , uint8_t Dev_Address ,uint8_t *Data_Out , uint8_t Data_Length ,Stop_Condition Stop , Start_Condition Start )
{
	/* TODO Support timeout (configure timer working for specific duration rise interrupt)
	 * TODO Timer_interrupt(){flag =}
	 * TODO so any code exist in while (check flag || any polling conditions)
	 */


	uint8_t i ;

	// Set the start bit in the I2C_CR1 register to generate a start condition from this will start as master
	I2C_Generate_Start(I2Cx, Enable, Start);

	/* Wait for EV5 */
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!(I2C_Get_FlagStatus(I2Cx, EV5)));

	//Writing DR register with Address, Send Address
	I2C_Send_Address(I2Cx, Dev_Address, Transmitter);

	/* Wait for EV6 */
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.

	while(!(I2C_Get_FlagStatus(I2Cx, EV6)));

	/*Wait for EV8_1 */
	/* EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR. */
	/* Check for TRA: Transmitter/receiver, BUSY: Bus busy, MSL: Master/slave, TxE Flags */
	while(!(I2C_Get_FlagStatus(I2Cx, Master_Transmitter_Event)));


	//Check if there is Data length available
	for(i = 0 ; i < Data_Length ; ++i )
	{
		//Write in the DR register the data to be sent
		I2Cx->I2C_DR = Data_Out[i];

		/* 7. Wait for EV8 */
		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register.
		while(!(I2C_Get_FlagStatus(I2Cx, EV8)));

	}

	//Send Stop Condition
	if(Stop == With_Stop)
		I2C_Generate_Stop(I2Cx, Enable);

}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- Dev_Address : slave address
 * @param [in] 		- Data_in : a pointer to the data which will be send
 * @param [in] 		- Data_Length : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_Rx(I2C_Typedef *I2Cx , uint8_t Dev_Address ,uint8_t *Data_in , uint8_t Data_Length ,Stop_Condition Stop , Start_Condition Start )
{
	/* TODO Support timeout (configure timer working for specific duration rise interrupt)
	 * TODO Timer_interrupt(){flag =}
	 * TODO so any code exist in while (check flag || any polling conditions)
	 */


	uint8_t i ;
	uint8_t index = (I2Cx ==  I2C1)? I2C1_Index : I2C2_Index ;
	// Set the start bit in the I2C_CR1 register to generate a start condition from this will start as master
	I2C_Generate_Start(I2Cx, Enable, Start);

	/* Wait for EV5 */
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!(I2C_Get_FlagStatus(I2Cx, EV5)));

	//Writing DR register with Address, Send Address
	I2C_Send_Address(I2Cx, Dev_Address, Receiver);

	/* Wait for EV6 */
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.

	while(!(I2C_Get_FlagStatus(I2Cx, EV6)));

	I2C_ACKConfig(I2Cx, Enable);

	if(Data_Length)
	{
		for(i = Data_Length ; i>1 ; i--)
		{
			//Wait for EV7
			//EV7: RxNE=1 cleared by reading DR register

			while(!(I2C_Get_FlagStatus(I2Cx, EV7)));

			//Read the data in the DR register
			*Data_in = I2Cx->I2C_DR ;

			//go to next address
			Data_in++ ;

		}

		//		To generate the non-acknowledge pulse after the last received data byte, the ACK bit
		//		must be cleared just after reading the second last data byte (after second last RxNE event).

		I2C_ACKConfig(I2Cx, Disable);
	}


	if(Stop == With_Stop)
		I2C_Generate_Stop(I2Cx, Enable); //send stop condition

	//re- enable ACK
	if(G_I2C_Config[index].ACK_Control == I2C_ACK_Control_Enable)
		I2C_ACKConfig(I2Cx, Enable);

}

/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_TX
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- TxData : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */
void MCAL_I2C_Slave_TX(I2C_Typedef *I2Cx, uint8_t data)
{
	I2Cx->I2C_DR = data;
}
/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_RX
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_Slave_RX(I2C_Typedef *I2Cx)
{
   return (I2Cx->I2C_DR);
}

/* ================================================================ */
/* ======================== Generic APIs ========================== */
/* ================================================================ */

void I2C_Generate_Start(I2C_Typedef *I2Cx ,Functional_State NewState , Start_Condition Start)
{
	//Check the type of start (Start or Repeated Start)
	if(Start != Repeated_Start)
	{
		// Check if the bus is idle
		while(I2C_Get_FlagStatus(I2Cx, Bus_Busy));
	}

	//  I2C_CR1  Bit 8 START: Start generation
	//       This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//       In Master Mode:
	//       0: No Start generation
	//       1: Repeated start generation
	//       In Slave mode:
	//       0: No Start generation
	//       1: Start generation when the bus is free

	if(NewState != Disable)
	{
		//Generate a START condition
		I2Cx->I2C_CR1 |= I2C_CR1_START ;
	}
	else
	{
		//Disable the START condition generation
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START) ;
	}

}

I2C_FlagStatus I2C_Get_FlagStatus(I2C_Typedef *I2Cx ,Status Flag )
{

	uint32_t Flag_1 = 0, Flag_2 = 0, Last_Event;
	I2C_FlagStatus Bit_status =Reset ;

	switch(Flag)
	{
	case Bus_Busy :
	{
		//I2C_SR2. Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0)
		if((I2Cx->I2C_SR2) & (I2C_SR2_BUSY))
			Bit_status = Set ;
		else
			Bit_status = Reset ;

		break ;
	}

	case EV5 :
	{

		//		 *I2C_SR1. Bit 0 SB: Start bit (Master mode)
		//					0: No Start condition
		//					1: Start condition generated.
		//			   – Set when a Start condition generated.
		//			   – Cleared by software by reading the SR1 register followed by writing the DR register, or by hardware when PE=0

		if((I2Cx->I2C_SR1) & (I2C_SR1_SB))
			Bit_status = Set ;
		else
			Bit_status = Reset ;

		break ;
	}

	case EV6 :
	{
		//	 I2C_SR1	Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//					This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.
		//
		//					Address matched (Slave)
		//					0: Address mismatched or not received.
		//					1: Received address matched.
		//					– Set by hardware as soon as the received slave address matched with the OAR registers
		//					content or a general call (when enabled depending on configuration).
		//					Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
		//					SR1 then READ SR2) after ADDR is set.
		//
		//					Address sent (Master)
		//					0: No end of address transmission
		//					1: End of address transmission
		//					– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
		//					– For 7-bit addressing, the bit is set after the ACK of the byte.
		//
		//					Note: ADDR is not set after a NACK reception

		if(I2Cx->I2C_SR1 & I2C_SR1_ADDR )
			Bit_status = Set ;
		else
			Bit_status = Reset ;

		break ;
	}

	case EV7_1:
	case EV7:
	{
		//		I2C_SR1. Bit 6 RxNE: Data register not empty (receivers)
		//						0: Data register empty
		//						1: Data register not empty
		//						– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//						– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//						RxNE is not set in case of ARLO event.
		//						Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.

		if((I2Cx->I2C_SR1) & (I2C_SR1_RXNE))
			Bit_status = Set;
		else
			Bit_status = Reset;
		break;
	}

	case EV8_1:
	case EV8 :
	{
		//		I2C_SR1.  Bit 7 TxE: Data register empty (transmitters)
		//						0: Data register not empty
		//						1: Data register empty
		//						– Set when DR is empty in transmission. TxE is not set during address phase.
		//						– Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0.

		if((I2Cx->I2C_SR1) & (I2C_SR1_TXE))
			Bit_status = Set;
		else
			Bit_status = Reset;
		break;

	}
	case Master_Transmitter_Event :
	{
		/* Check if BUSY ,TRA ,MSL W,TXE flags are all set */

		/*Read the I2C status register */
		Flag_1 = Master_Transmitter_Event & (0x0000FFFF);
		Flag_2 = Master_Transmitter_Event >> 16;

		/* Get the last event value form the I2C status registers */
		Last_Event = ((I2Cx->I2C_SR1 & Flag_1) | ((I2Cx->I2C_SR2 & Flag_2) << 16) );

		if(Last_Event == Flag)
			Bit_status = Set;
		else
			Bit_status = Reset;
		break;
	}

	}
	return Bit_status ;
}

void I2C_Send_Address(I2C_Typedef *I2Cx , uint8_t Dev_Address , I2C_Direction Direction)
{
	//Support 7-bit address mode only
	if(Direction == Receiver)
	{
		//Set the address bit 0 for read
		I2Cx->I2C_DR = (Dev_Address << 1 | (0x01) );
	}
	else
	{
		//Reset the address bit 0 for write
		I2Cx->I2C_DR = (Dev_Address << 1 );
	}
}

void I2C_Generate_Stop(I2C_Typedef *I2Cx ,Functional_State NewState)
{
	//I2C_CR1	Bit 9 STOP: Stop generation
	//	The bit is set and cleared by software, cleared by hardware when a Stop condition is
	//	detected, set by hardware when a timeout error is detected.
	//	In Master Mode:
	//	0: No Stop generation.
	//	1: Stop generation after the current byte transfer or after the current Start condition is sent.
	//	In Slave mode:
	//	0: No Stop generation.
	//	1: Release the SCL and SDA lines after the current byte transfer
	if(NewState == Enable)
	{
		// Generate a stop condition, Enable stop bit
		I2Cx->I2C_CR1 |= (I2C_CR1_STOP);
	}
	else
	{
		//Disable the stop condition generation, Disable stop bit
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP);
	}
}

void I2C_ACKConfig(I2C_Typedef *I2Cx, Functional_State State)
{
	if(State == Enable)
	{
		/* Enable Automatic ACK */
		I2Cx->I2C_CR1 |= (I2C_CR1_ACK);
	}
	else
	{
		/* Disable Automatic ACK */
		I2Cx->I2C_CR1 &= ~(I2C_CR1_ACK);
	}
}
