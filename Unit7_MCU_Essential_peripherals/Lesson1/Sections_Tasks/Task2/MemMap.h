/*
 * MemMap.h
 *
 * Created: 10/12/2023 7:30:30 PM
 *  Author: elmag
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

//port A
#define DDRA  *(volatile unsigned char*)(0x3A)
#define PORTA *(volatile unsigned char*)(0x3B)
#define PINA  *(volatile unsigned char*)(0x39)

//port C
#define DDRC  *(volatile unsigned char*)(0x34)
#define PORTC *(volatile unsigned char*)(0x35)
#define PINC  *(volatile unsigned char*)(0x33)
#endif /* MEMMAP_H_ */