/*
 * Atmega_SPI_Lab.c
 *
 * Created: 2/15/2024 11:29:22 AM
 * Author : Elmag
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7
void SPI_Master_Init(void)
{
	//set MOSI and SCK and SS pins as output
	DDRB |=(1<<SS)|(1<<MOSI)|(1<<SCK);
	
	//enable SPI , master mode , clock rate fck/16
	SPCR |=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_Master_Transmit(uint8_t cmd , uint8_t data)
{  
  PORTB &= ~(1<<SS);
  
  SPDR = cmd ;
  
  while(!(SPSR&(1<<SPIF)));
  
  
  SPDR =data ;
  
  while(!(SPSR&(1<<SPIF)));
  
  PORTB |=(1<<SS);
}

int main(void)
{
	uint8_t count = 0 ;
	uint8_t i =0;
	
	SPI_Master_Init();
	
    SPI_Master_Transmit(0x09, 0xFF);
	
	SPI_Master_Transmit(0x0A , 0x0F);
	
	SPI_Master_Transmit(0x0B , 0x07);
	
	SPI_Master_Transmit(0x0C , 0x01);
	
	while(1)
	{
		for(i = 1; i<9;i++)
		{
			SPI_Master_Transmit(i,count++);
			_delay_ms(300);
		}
		
		for(i= 1 ;i<9 ; i++)
		{
			SPI_Master_Transmit(i,0);
		}
	} 
}
