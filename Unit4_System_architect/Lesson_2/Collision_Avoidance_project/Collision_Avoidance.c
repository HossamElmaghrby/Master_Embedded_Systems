/*
 ============================================================================
 Name        : Collision_Avoidance.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "CA.h"
#include "US.h"
#include "DC.h"
void setup()
{
	//init all the drivers
	//init IRQ .....
	//init HAL US_Driver DC_Driver
	//init Block
	//set STates pointer for each block
	CA_state = STATE(CA_waiting) ;
	US_state = STATE(US_busy) ;
	DC_state = STATE(DC_idle) ;
}
int main(void) {

	setup();
	while(1)
	{
		US_state();
		CA_state();
		DC_state();
	}
	return EXIT_SUCCESS;
}
