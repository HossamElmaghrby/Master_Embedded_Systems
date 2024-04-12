/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Elmag
 */

#include "EEPROM/I2C_Slave_EEPROM.h"

void HAL_EEPROM_Init(void)
{
    I2C_Config I2C_Cfg ;

    I2C_Cfg.ACK_Control = I2C_ACK_Control_Enable ;
    I2C_Cfg.Clock_Frequency = I2C_Clock_Frequency_SM_100KHZ ;
    I2C_Cfg.Clock_Stretching = I2C_Clock_Stretch_Enable ;
    I2C_Cfg.General_Call = I2C_General_Call_Enable ;
    I2C_Cfg.Master_Mode = I2C_Master_Mode_SM ;
    I2C_Cfg.Mode = I2C_Mode_I2C_Mode ;
    I2C_Cfg.p_slave_CallBack = NULL ;

    MCAL_I2C_Init(I2C1, &I2C_Cfg);
    MCAL_I2C_GPIO_Set_Pin(I2C1);
}
uint8_t HAL_EEPROM_Write_Nbytes(uint16_t Memory_Address , uint8_t *Byte , uint8_t Data_Length)
{
   int  i = 0 ;

   uint8_t buffer[255] ;

   buffer[0] = (uint8_t)(Memory_Address >> 8);  //upper byte Memory address
   buffer[1] = (uint8_t)(Memory_Address);       //lower byte Memory address

   for(i= 2 ; i < (Data_Length + 2) ; i++)
   {
	   buffer[i]= Byte[i-2];
   }

   MCAL_I2C_Master_Tx(I2C1, EEPROM_Slave_Address, buffer, (Data_Length + 2), With_Stop, Start);

   return 0 ;


}
uint8_t HAL_EEPROM_Read_Nbytes(uint16_t Memory_Address , uint8_t *Byte , uint8_t Data_Length)
{
   uint8_t buffer[2] ;

   buffer[0] = (uint8_t)(Memory_Address >> 8);    //upper byte Memory address
   buffer[1] = (uint8_t)(Memory_Address);         //lower byte Memory address

   MCAL_I2C_Master_Tx(I2C1, EEPROM_Slave_Address , buffer, 2, Without_Stop, Start);
   MCAL_I2C_Master_Rx(I2C1, EEPROM_Slave_Address, Byte, Data_Length, With_Stop, Repeated_Start);

   return 0 ;
}
