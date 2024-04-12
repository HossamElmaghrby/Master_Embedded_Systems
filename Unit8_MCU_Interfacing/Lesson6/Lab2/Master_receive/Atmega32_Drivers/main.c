/*
 * Atmega32_Drivers.c
 *
 * Created: 12/14/2023 8:26:01 AM
 * Author : Elmag
 */ 

#include "LCD/lcd.h"
#include "Atmega32_SPI_Driver.h"


int main(void)
{
   unsigned char ch;
   DDRA=0xFF;                                   //PORTA is Output
   I2C_Init(0x48);                             //Initialize TWI for Master Code
   while (1)
   {
	   _delay_ms(1000);
	   I2C_Start();                       //Transmit Start condition
	   I2C_Write(0b11010000+1);          //Transmit SLA+R(1)
	   ch=I2C_Read(0);                  //read last Byte , send NACK
	   I2C_Stop();
	   PORTA=ch;
   }
}
