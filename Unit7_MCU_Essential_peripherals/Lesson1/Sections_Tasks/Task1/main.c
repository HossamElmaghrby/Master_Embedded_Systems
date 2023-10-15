/*
 * serial_Led.c
 *
 * Created: 10/11/2023 7:47:39 PM
 * Author : elmag
 */ 

#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	DDRA =0xff ;
	/* Replace with your application code */
	while (1)
	{
		volatile unsigned char i ;
		for(i = 0; i<8 ; i++)
		{
			SetBit(PORTA,i);
			_delay(1000);
		}
		for(i =7 ;i>=0;i--)
		{
			ResetBit(PORTA,i);
			_delay(1000);
		}
	}
}

