/*
 * Atmega32_I2C_Driver.h
 *
 * Created: 4/11/2024 11:19:45 AM
 *  Author: Elmag
 */ 


#ifndef ATMEGA32_I2C_DRIVER_H_
#define ATMEGA32_I2C_DRIVER_H_

#include "Atmega32_Device_Header.h"

void I2C_Init(unsigned long SCL_Clock);
void I2C_Start(void);
void I2C_Write(unsigned char Byte);
unsigned char I2C_Read();
void I2C_Stop();



#endif /* ATMEGA32_I2C_DRIVER_H_ */