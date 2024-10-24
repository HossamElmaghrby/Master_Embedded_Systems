/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "Scheduler.h"
#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_Driver.h"
#include "stm32f103x6_EXTI_Driver.h"
#include "core_cm3.h"

Task_Ref Task1 , Task2 ,Task3 ,Task4 ;

uint8_t Task1LED,Task2LED,Task3LED,Task4LED ;

Mutex_ref Mutex1 ;
uint8_t payload[3]={1,2,3};

void task1()
{
	static int Count = 0 ;
	while(1)
	{
		Task1LED ^=1 ;
		Count++ ;
		if(Count == 100)
		{
			MYRTOS_AcquireMutex(&Mutex1, &Task1);
			MYRTOS_ActivateTask(&Task2);
		}
		if(Count == 200)
		{
			Count = 0 ;
			MYRTOS_ReleaseMutex(&Mutex1);
		}
	}
}

void task2()
{
	static int Count = 0 ;
	while(1)
	{
		Task2LED ^=1 ;
		Count++ ;
		if(Count == 100)
		{
			MYRTOS_ActivateTask(&Task3);

		}
		if(Count == 200)
		{
			Count = 0 ;
			MYRTOS_TerminateTask(&Task2);
		}
	}
}

void task3()
{
	static int Count = 0 ;
	while(1)
	{
		Task3LED ^=1 ;
		Count++ ;
		if(Count == 100)
		{

			MYRTOS_ActivateTask(&Task4);
		}

		if(Count == 200)
		{
			Count = 0 ;
			MYRTOS_TerminateTask(&Task3);
		}
	}
}


void task4()
{
	static int Count = 0 ;
	while(1)
	{
		Task4LED ^=1 ;
		Count++ ;

		if(Count == 5 )
		{
			MYRTOS_AcquireMutex(&Mutex1, &Task4);
		}
		if(Count == 200)
		{
			Count = 0 ;
			MYRTOS_ReleaseMutex(&Mutex1);
			MYRTOS_TerminateTask(&Task4);
		}
	}
}
int main(void)
{

	MYRTOS_errorID Error = NOError;

	//HW_init (Initialization clock Tree , RestController)
	HW_Init();
	if( MYRTOS_Init() != NOError )
	{
		while(1);
	}


	strcpy((char*)Mutex1.MutexName, "Mutex1");
	Mutex1.PayloadSize = 3;
	Mutex1.Ppayload =(uint8_t*)payload ;


	Task1.Stack_Size = 512 ;
	Task1.P_TaskEntry = task1 ;
	Task1.Priority = 4 ;
	strcpy((char*)Task1.TaskName, "task_1");

	Task2.Stack_Size = 512 ;
	Task2.P_TaskEntry = task2 ;
	Task2.Priority = 3 ;
	strcpy((char*)Task2.TaskName, "task_2");

	Task3.Stack_Size = 512 ;
	Task3.P_TaskEntry = task3 ;
	Task3.Priority = 2 ;
	strcpy((char*)Task3.TaskName, "task_3");

	Task4.Stack_Size = 512 ;
	Task4.P_TaskEntry =task4;
	Task4.Priority= 1 ;
	strcpy ((char*)Task4.TaskName, "task_4");

	Error += MYRTOS_CreateTask(&Task1);
	Error += MYRTOS_CreateTask(&Task2);
	Error += MYRTOS_CreateTask(&Task3);
	Error += MYRTOS_CreateTask(&Task4);


	MYRTOS_ActivateTask(&Task1);

	MYRTOS_STARTOS() ;

	while(1)
	{

	}
}
