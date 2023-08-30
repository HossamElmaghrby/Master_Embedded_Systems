/*
 ============================================================================
 Name        : Circular.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "queue.h"

#define buffer1_length 5
elment_type buffer1[buffer1_length] ;


void main(void) {
	FIFO_Buf_t uart_fifo ;
	unsigned char i , temp =0;
	if(FIFO_init(&uart_fifo, buffer1, buffer1_length)==FIFO_no_erro)
		printf("FIFO init----DONE \n");

	for(i=0;i<7;i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&uart_fifo, &i)==FIFO_no_erro)
			printf("FIFO Enqueue (%x)--- DONE \n",i);
		else
			printf("FIFO Enqueue (%x)--- FAILED\n",i);
	}
	FIFO_print(&uart_fifo) ;
	FIFO_dequeue(&uart_fifo, &temp);
	printf("FIFO_dequeu : Data=%x \n",temp);
	FIFO_dequeue(&uart_fifo, &temp);
	printf("FIFO_dequeu : Data=%x \n",temp);

	for(i =0; i<2 ;i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&uart_fifo, &i)==FIFO_no_erro)
			printf("FIFO Enqueue (%x)--- DONE \n",i);
		else
			printf("FIFO Enqueue (%x)--- FAILED\n",i);
	}
	FIFO_print(&uart_fifo) ;
}

