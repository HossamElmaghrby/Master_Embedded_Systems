#include "uart.h"

unsigned char string_buffer[100]="learn-in-depth:Hossam Elmaghrby";
 unsigned const char string_buffer2[100]="learn-in-depth:Hossam Elmaghrby";
void main(void)
{
	Uart_Send_String(string_buffer);
}