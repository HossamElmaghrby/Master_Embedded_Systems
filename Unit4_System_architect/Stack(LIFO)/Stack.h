/*
 * Stack
 *
 *  Created on: Aug 28, 2023
 *      Author: elmag
 */


#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Dprintf(...) fflush(stdout);printf(__VA_ARGS__);fflush(stdout);
#define Size 5
int Stack[Size] ;
//APIs
void push();
int pop();
int peek();
void Display();
bool isEmpty();
bool isFull();

#endif /* STACK_H_ */
