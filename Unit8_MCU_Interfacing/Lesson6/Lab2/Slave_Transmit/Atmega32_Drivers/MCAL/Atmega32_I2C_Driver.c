/*
 * Atmega32_I2C_Driver.c
 *
 * Created: 4/11/2024 5:56:14 PM
 *  Author: Elmag
 */ 

#include "Atmega32_I2C_Driver.h"

void I2C_Set_Address(unsigned char address)
{
	TWAR = address ;
}
unsigned char I2C_Read()
{
	unsigned char x=0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & 0x80) == 0);
	
}
void I2C_Write(unsigned char Byte)
{
	TWDR = Byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & 0x80)==0);
}