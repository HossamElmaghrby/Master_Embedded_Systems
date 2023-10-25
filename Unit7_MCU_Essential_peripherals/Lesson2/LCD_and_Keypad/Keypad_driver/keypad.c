/*
 * keypad.c
 *
 * Created: 10/24/2023 11:49:01 AM
 *  Author: elmag
 */ 

#include "Keypad.h"

int keypad_row[]= {R0,R1,R2,R3} ;
int keypad_col[]= {C0,C1,C2,C3} ;

void Keypad_init()
{
	Keypad_DDR &= ~ (1<<R0) | (1<<R1) |(1<<R2) |(1<<R3);
    Keypad_DDR |=  (1<<C0) | (1<<C1) |(1<<C2) |(1<<C3);
	
	keypad_PORT =0xFF ;
}

char Keypad_getkey()
{
	int i ,j ;
	for(i =0 ;i<4 ;i++)
	{
		keypad_PORT |=((1<<keypad_col[0]) |(1<<keypad_col[1]) | (1<<keypad_col[2]) | (1<<keypad_col[3]));
		keypad_PORT &=~(1<<keypad_col[i]);
		
		for(j= 0 ;j<4 ;j++)
		
		if(!(keypad_PIN & (1<<keypad_row[j])))
		{
			while(!(keypad_PIN & (1<<keypad_row[j])));
			switch(i)
			{
				
				case 0:
					if(j==0)      return '7';
					else if(j==1) return '4';
					else if(j==2) return '1';
					else if(j==3) return '?';
					break;
				case 1:
					if(j==0)      return '8';
					else if(j==1) return '5';
					else if(j==2) return '2';
					else if(j==3) return '0';
				break;
				case 2:
					if(j==0)      return '9';
					else if(j==1) return '6';
					else if(j==2) return '3';
					else if(j==3) return '=';
				break;
				case 3:
					if(j==0)      return '/';
					else if(j==1) return '*';
					else if(j==2) return '-';
					else if(j==3) return '+';
				break;
			}
		}
	}
	return 'A' ;
}		