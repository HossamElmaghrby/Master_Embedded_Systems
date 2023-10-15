/*
 * Unite7_Lesson_lab2.c
 *
 * Created: 10/13/2023 7:08:59 PM
 * Author : elmag
 */ 

#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000UL


int main(void)
{
	DDRD=0xff ;
    while (1) 
    {
		SetBit(PORTD,5);
		_delay(1000);
		PORTD =0x00 ;
		SetBit(PORTD,6);
		_delay(1000);
		PORTD =0x00;
		SetBit(PORTD,7);
		_delay(1000);
		PORTD =0x00;
		SetBit(PORTD,4);
		_delay(1000);
		PORTD =0x00;
    }
}

