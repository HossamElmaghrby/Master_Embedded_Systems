/*
 * I2C.h
 *
 * Created: 4/11/2024 5:55:02 PM
 *  Author: Elmag
 */ 


#ifndef I2C_H_
#define I2C_H_
#include "Atmega32_Device_Header.h"

void I2C_Set_Address(unsigned char address);
unsigned char I2C_Read();
void I2C_Write(unsigned char Byte);

#endif /* I2C_H_ */