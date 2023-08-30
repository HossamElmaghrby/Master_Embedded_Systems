/*
 * Stack.c
 *
 *  Created on: Aug 28, 2023
 *      Author: elmag
 */
#include "Stack.h"

int top= -1 ;
void push()
{
	if(isFull())
	{
		Dprintf("Stack overflow: can't add more elements\n");
	}
	else
	{
		int x ;
		Dprintf("Enter element: ");
		scanf("%d",&x);
		top++;
		Stack[top] = x;
	}
}
int pop()
{
   if(isEmpty())
   {
	   Dprintf("Stack Underflow: Stack already empty\n");
   }
   else
   {
	   int x=Stack[top];
	   Dprintf("%d is deleted from the stack\n",x);
	   top--;
	   return x;
   }
   return -1;
}
int peek()
{
	if(isEmpty())
	{
		Dprintf("Stack is empty\n");
		return -1 ;
	}
	else
	{
		int x=Stack[top];
		Dprintf("%d is the top of the stack\n",x);
		return x;
	}
}
void Display()
{
	if(isEmpty())
	{
		Dprintf("Stack is empty\n");
	}
	else
	{
		Dprintf("elements of the stack is\n")
		for(int i=top;i>=0;i--)
		{
			Dprintf("%d ",Stack[i]);
		}
		Dprintf("\n");
	}

}
bool isEmpty()
{
	if(top==-1)
		return true;

	return false ;
}
bool isFull()
{
	if(top==Size-1)
		return true;

	return false;
}
