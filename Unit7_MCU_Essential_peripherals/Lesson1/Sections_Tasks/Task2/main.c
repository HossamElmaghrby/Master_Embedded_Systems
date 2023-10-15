/*
 * serial_led_using_button.c
 *
 * Created: 10/12/2023 7:23:44 PM
 * Author : elmag
 */ 

#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000UL
int main(void)
{
	DDRA =0xff ;
	ResetBit(DDRC,0);
	SetBit(PORTC,0);
	
	volatile unsigned char count =0;
	while (1)
	{
        if(ReadBit(PINC,0)==0)
		{
			SetBit(PORTA,count);
			count++;
			while(ReadBit(PINC,0)==0);
			if(count==8)
			while(count)
			{
				if(ReadBit(PINC,0)==0)
				{
				count--;
				ResetBit(PORTA,count);
				while(ReadBit(PINC,0)==0);
				}
			}
			
		}	   
	}
}

