/*
 * MemMap.h
 *
 * Created: 10/12/2023 7:30:30 PM
 *  Author: elmag
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

//port D
#define DDRD  *(volatile unsigned char*)(0x31)
#define PORTD *(volatile unsigned char*)(0x32)

#endif /* MEMMAP_H_ */