/*
 * Secheduler.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Elmag
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include "CortexMX_OS_Porting.h"

typedef enum
{
	NOError ,
	Ready_QUEUE_init_error,
	Task_exceeded_StackSize,
	MutexisReacedToMaxNumberOfUsers
}MYRTOS_errorID;


typedef struct
{
	uint32_t Stack_Size ;
	uint8_t Priority ;
	void (*P_TaskEntry)(void) ;
	uint8_t AutoStart ;
	uint32_t  _S_PSP_Task ;  //Not Entered by the user
	uint32_t  _E_PSP_Task ;  //Not Entered by the user
	uint32_t* Current_PSP ;  //Not Entered by the user
	uint8_t TaskName[30];

	enum
	{
		Suspend,
		Waiting,
		Ready,
		Running
	}TaskState;

	struct
	{
		enum
		{
			enable,
			disable
		}Blocking;
		uint32_t Ticks_Count ;

	}TimingWaiting;
}Task_Ref;

typedef struct
{
	uint8_t Ppayload ;
	uint32_t PayloadSize ;
	Task_Ref* CurrentTUser ;
	Task_Ref* NextTUser ;
	uint8_t MutexName[30] ;
}Mutex_ref;

MYRTOS_errorID MYRTOS_Init();
MYRTOS_errorID MYRTOS_CreateTask(Task_Ref* Tref);
void MYRTOS_ActivateTask(Task_Ref * Tref);
void MYRTOS_TerminateTask(Task_Ref * Tref);
void MYRTOS_TaskWait(uint32_t NOFTICKS , Task_Ref * SelfTRef);
void MYRTOS_Update_TasksWaitingTime();
MYRTOS_errorID MYRTOS_AcquireMutex(Mutex_ref* Mref , Task_Ref* Tref);
void MYRTOS_ReleaseMutex(Mutex_ref* Mref);
void MYRTOS_STARTOS();
#endif /* INC_SCHEDULER_H_ */
