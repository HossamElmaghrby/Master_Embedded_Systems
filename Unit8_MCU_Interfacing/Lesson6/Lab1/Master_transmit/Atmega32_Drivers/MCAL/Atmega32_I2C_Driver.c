/*
 * Atmega32_I2C_Driver.c
 *
 * Created: 4/11/2024 11:21:24 AM
 *  Author: Elmag
 */ 
#include "Atmega32_I2C_Driver.h"

#define prescaler 1 
void I2C_Init(unsigned long SCL_Clock)
{
	TWBR = (unsigned char)(((F_CPU/SCL_Clock)-16)/(2*prescaler));
	
	if(prescaler == 0)
	TWSR = 0 ;
	else if (prescaler == 4)
	TWSR = 1 ;
	else if (prescaler == 16)
	TWSR = 2;
	else if (prescaler == 64)
	TWSR = 3;
}
void I2C_Start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR)!=0x08);
}
void I2C_Write(unsigned char Byte)
{
	TWDR = Byte ;
	TWCR =(1<<TWINT)|(1<<TWEN);
	while ((TWCR & 0x80)==0);
}
unsigned char I2C_Read()
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while ((TWCR & 0x80)==0);
	return TWDR;
	
}
void I2C_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}