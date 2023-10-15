/*
 * Utils.h
 *
 * Created: 10/11/2023 7:48:53 PM
 *  Author: elmag
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg,bit)  reg|=(1<<bit)

#define ResetBit(reg,bit) reg&=~(1<<bit)

#define ToggleBit(reg,bit) reg^=(1<<bit)

#define ReadBit(reg,bit)   ((reg>>bit) & 1)

void _delay(unsigned char time)
{
	volatile unsigned char count ,i,k ;
	for(count =0 ;count<time;count++)
	{
	    for(i=0 ;i<255 ;i++);
		for(k=0 ;k<255 ;k++);
	}
}
#endif /* UTILS_H_ */