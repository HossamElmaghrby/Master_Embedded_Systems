/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 


#include "Atmega32_I2C_Driver.h"
int main(void)
{
   DDRA=0xFF;
   I2C_Set_Address(0b11010000);         //Enable slave at address 01101000 and Don't accept general call
   while (1)
   {
	   PORTA = I2C_Read(1);             // Receive Byte and send ACK
   }
   return 0;
}
