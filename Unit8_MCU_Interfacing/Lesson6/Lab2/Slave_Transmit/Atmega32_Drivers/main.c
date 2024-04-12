/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 


#include "Atmega32_I2C_Driver.h"
int main(void)
{
    unsigned char ch=0;
    I2C_Set_Address(0b11010000);     //Set Slave Address
    while (1)
    {
	    I2C_Read(1);              //Read Byte send ACK
	    I2C_Write(ch++);         //SLA(1001100)+R(1)
    }
   return 0;
}
