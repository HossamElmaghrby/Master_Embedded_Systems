/*
 * Unit6_Lesson4_lab3.c
 *
 * Created: 10/4/2023 11:24:40 AM
 * Author : elmag
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define MCU_BASE 0x20

#define MCU_MCUCR  *(volatile unsigned int *)(MCU_BASE + 0x35)
#define MCU_MCUCSR *(volatile unsigned int *)(MCU_BASE + 0x34)
#define MCU_GICR   *(volatile unsigned int *)(MCU_BASE + 0x3B)
#define MCU_GIFR   *(volatile unsigned int *)(MCU_BASE + 0x3A)
#define MCU_SREG   *(volatile unsigned int *)(MCU_BASE + 0x3F)

int main(void)
{
	//configuration MCU Control Register to sense interrupt
	// INT0 -> Any logical change
	MCU_MCUCR |=(1<<0);
	MCU_MCUCR &=~(1<<1);//already is rest
	// INT1 -> Rising edge
	MCU_MCUCR |=(1<<2);
	MCU_MCUCR |=(1<<3);
	// INT2 -> Falling edge
	MCU_MCUCSR &=~(1<<6);//already is rest
	
	//Enable External interrupt bits
	//Enable INT0
	MCU_GICR |=(1<<6);
	//Enable INT1
	MCU_GICR |=(1<<7);
	//Enable INT2
	MCU_GICR |=(1<<5);
	
	//Enable Global interrupt
	sei();
	
	// Port D pins(5,6,7) set direction to output
	DDRD |=(1<<5);
	DDRD |=(1<<6);
	DDRD |=(1<<7);
	while (1)
	{
		PORTD &=0b00011111;
	}
}

ISR(INT0_vect)
{
	//turn on led
	PORTD |=(1<<5);
	
	//wait 1 second
	_delay_ms(500);
	
	//clear INT0
	MCU_GIFR |=(1<<6);
}

ISR(INT1_vect)
{
	//turn on led
	PORTD |=(1<<6);
	
	//wait 1 second
	_delay_ms(500);
	
	//Enable INT1
	MCU_GIFR |=(1<<7);

	
}

ISR(INT2_vect)
{
	//turn on led
	PORTD |=(1<<7);
	
	//wait 1 second
	_delay_ms(500);
	
	//Enable INT2
	MCU_GIFR |=(1<<5);
}

