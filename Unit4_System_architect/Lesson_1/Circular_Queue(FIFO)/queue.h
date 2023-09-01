/*
 * queue.h
 *
 *  Created on: Aug 28, 2023
 *      Author: elmag
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "stdio.h"
#include "stdint.h"

#define elment_type uint8_t

typedef struct
{
	unsigned int length ;
	elment_type *base ;
	elment_type *tail ;
	elment_type *head ;
	unsigned int count ;
}FIFO_Buf_t;

typedef enum
{
	FIFO_no_erro,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}E_Buffer_Status;

E_Buffer_Status FIFO_enqueue(FIFO_Buf_t *fifo ,elment_type *ENQ_Data);
E_Buffer_Status FIFO_dequeue(FIFO_Buf_t *fifo ,elment_type *ENQ_Data);
E_Buffer_Status FIFO_Is_Buf_Full(FIFO_Buf_t *fifo);
E_Buffer_Status FIFO_print(FIFO_Buf_t*fifo);
E_Buffer_Status FIFO_init(FIFO_Buf_t* fifo, elment_type*buff,uint32_t buff_length);


#endif /* QUEUE_H_ */
