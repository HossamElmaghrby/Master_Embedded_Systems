/*
 * queue.c
 *
 *  Created on: Aug 28, 2023
 *      Author: elmag
 */
#include "queue.h"
E_Buffer_Status FIFO_init(FIFO_Buf_t* fifo, elment_type*buff,uint32_t buff_length)
{
	fifo->base =buff;
	fifo->head =fifo->base;
    fifo->tail =fifo->base;
    fifo->length =buff_length;
    fifo->count=0;

    if(fifo->base && fifo->length)
    	return FIFO_no_erro ;
    else
    	return FIFO_null;
}
E_Buffer_Status FIFO_Is_Buf_Full(FIFO_Buf_t *fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null ;

	if(fifo->count>= fifo->length)
	{
		printf("FIFO is full\n");
		return FIFO_full;
	}
	return FIFO_no_erro;
}

E_Buffer_Status FIFO_enqueue(FIFO_Buf_t *fifo ,elment_type *ENQ_Data)
{
   if(FIFO_Is_Buf_Full(fifo)==FIFO_no_erro)
   {
	   *(fifo->head)=*ENQ_Data ;
	   fifo->count++;

	   if(fifo->head==(fifo->base + (fifo->length *sizeof(elment_type))))
		   fifo->head =fifo->base ;
	   else
		   fifo->head ++;

	   return FIFO_no_erro ;
   }
   else
   {
	    printf("FIFO ENQUEUE FAILED\n");
	    return (FIFO_Is_Buf_Full(fifo));
   }
}
E_Buffer_Status FIFO_dequeue(FIFO_Buf_t *fifo ,elment_type *DEQ_Data)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null ;
	if(fifo->count==0)
	{
		printf("FIFO is empty\n");
		return FIFO_empty ;
	}
	*DEQ_Data =*fifo->tail;
	fifo->count--;
	   if(fifo->tail==(fifo->base + (fifo->length *sizeof(elment_type))))
		   fifo->tail =fifo->base ;
	   else
		   fifo->tail ++;

	   return FIFO_no_erro ;
}
E_Buffer_Status FIFO_print(FIFO_Buf_t *fifo)
{
	elment_type *temp ;
	int i;
	if( fifo->count == 0 )
	{
		printf("FIFO is empty \n");
		return FIFO_empty;
	}
	temp = fifo->tail ;
	printf("\n======FIFO print=======\n");
	for(i=0;i< fifo->count ;i++)
	{
		printf("\t %X \n",*temp);
		temp++;
	}
	printf("\n=============\n");

}

