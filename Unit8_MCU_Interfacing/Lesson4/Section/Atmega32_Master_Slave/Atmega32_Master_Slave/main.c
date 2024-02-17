/*
 * Atmega_SPI_Lab.c
 *
 * Created: 2/15/2024 11:29:22 AM
 * Author : Elmag
 */ 
#define F_CPU 1000000UL

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7
#include <avr/io.h>
#include <util/delay.h>

void SPI_Master_Init(void)
{
	//set MOSI and SCK and SS pins as output
	DDRB |=(1<<SS)|(1<<MOSI)|(1<<SCK);
	
	//enable SPI , master mode , clock rate fck/16
	SPCR |=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_SlaveInit(void)
{
	 
	//set MOSI and SCK and SS pins as output
	DDRB &=~(1<<MISO) & ~(1<<SCK) &~(1<<SS);
	
	//enable SPI
	SPCR |=(1<<SPE);
}
void SPI_Master_Transmet(uint8_t data)
{
	//transmit data by writing on SPDR register
	SPDR = data ;
	//wait for transmit complete
	while(!(SPSR&(1<<SPIF)));
	
}

uint8_t SPI_Slave_Recieve(void)
{
		/* Return Data Register */
		return SPDR;
}
//==================== for master microcontroller ===============
int main(void)
{
	//set port A as output  for 7Segment 
    DDRA = 0xFF ; 
	
	SPI_Master_Init();
    for(int ch = 0; ch<=225 ; ch++)
	{
		_delay_ms(1000);
		PORTA = ch ;
	}
}
//==================for slave microcontroller ====================
/*int main(void)
{
	//set port A as output  for 7Segment
	DDRA = 0xFF;
	
	SPI_Slave_Init();
	while (1)
	{
		PORTA = SPI_Slave_Recieve();
	}
}*/