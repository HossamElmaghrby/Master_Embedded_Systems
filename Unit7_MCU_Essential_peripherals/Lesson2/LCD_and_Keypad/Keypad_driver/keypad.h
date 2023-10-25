/*
 * keypad.h
 *
 * Created: 10/24/2023 11:49:45 AM
 *  Author: elmag
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

//keypad information
#define R0 0
#define R1 1
#define R2 2
#define R3 3

#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define keypad_PORT PORTC
#define keypad_PIN PINC
#define Keypad_DDR DDRC

void Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_H_ */