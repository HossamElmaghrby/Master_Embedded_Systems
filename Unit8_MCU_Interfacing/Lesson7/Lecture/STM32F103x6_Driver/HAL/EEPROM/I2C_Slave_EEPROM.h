/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Mar 17, 2024
 *      Author: Elmag
 */

#ifndef EEPROM_I2C_SLAVE_EEPROM_H_
#define EEPROM_I2C_SLAVE_EEPROM_H_

#include "stm32f103x6_I2C_Driver.h"

#define EEPROM_Slave_Address      0x2A

// Idle Mode : The device is in high-Impedane state and waits for data.
// Master Transmitter Mode : The device transmits data to a slave receiver.
// Master Receiver Mode :The device receives data form a slave transmitter.

/* ============ APIs ============ */
void HAL_EEPROM_Init(void);

uint8_t HAL_EEPROM_Write_Nbytes(uint16_t Memory_Address , uint8_t *Byte , uint8_t Data_Length);
uint8_t HAL_EEPROM_Read_Nbytes(uint16_t Memory_Address , uint8_t *Byte , uint8_t Data_Length);

#endif /* EEPROM_I2C_SLAVE_EEPROM_H_ */
