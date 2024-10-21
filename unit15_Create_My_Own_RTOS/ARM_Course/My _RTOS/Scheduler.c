/*
 * Secheduler.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Elmag
 */


#include "Scheduler.h"
#include "MYRTOS_FIFO.h"


FIFO_Buf_t Ready_QUEUE ;

Task_Ref* Ready_QUEUE_FIFO[100] ;

Task_Ref MYRTOS_idleTask ;

uint8_t IdleTaskLED ;
struct
{
	Task_Ref* OSTasks[100] ;
	uint32_t  _S_MSP_Task ;
	uint32_t  _E_MSP_Task ;
	uint32_t PSP_Task_Locator ;
	uint32_t NoOfActiveTasks ;

	Task_Ref* CurrentTask ;
	Task_Ref* NextTask ;

	enum
	{
		OSSuspend,
		OSRunning

	}OSModeID;

}OS_Control;

typedef enum {
	SVC_Activatetask,
	SVC_terminateTask,
	SVC_TaskWaitingTime,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;

void MYRTOS_Cereate_MainStack()
{
	OS_Control._S_MSP_Task = (uint32_t)&_estack ;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task  - MainStackSize ;

	//aligned 8 Bytes Spaces between Main Task and PSP Task

	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8);
}

void MYRTOS_IdleTask()
{
	while(1)
	{
		IdleTaskLED ^= 1 ;
		__asm("WFE");
	}
}

MYRTOS_errorID MYRTOS_Init()
{
	MYRTOS_errorID Error = NOError ;

	//Update OS Mode ( Suspend )
	OS_Control.OSModeID = OSSuspend ;


	//Specify The MAIN Stack for OS
	MYRTOS_Cereate_MainStack();

	//create OS ready queue
	if(FIFO_init(&Ready_QUEUE,Ready_QUEUE_FIFO , 100) != FIFO_NO_ERROR)
	{
		Error += Ready_QUEUE_init_error ;
	}

	//configure IDLE TASK
	strcpy((char*)MYRTOS_idleTask.TaskName , "idleTask");
	MYRTOS_idleTask.Priority = 255 ;
	MYRTOS_idleTask.P_TaskEntry = MYRTOS_IdleTask ;
	MYRTOS_idleTask.Stack_Size = 300 ;

	Error += MYRTOS_CreateTask(&MYRTOS_idleTask);

	return Error ;
}


void MyRTOS_Create_TaskStack(Task_Ref* Tref)
{
	/*Task Frame
	 * ======
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 * r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */
	Tref->Current_PSP = (uint32_t *)Tref->_S_PSP_Task ;

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) =  0x01000000;         //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = (uint32_t) Tref->P_TaskEntry ;//PC

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = 0xFFFFFFFD ;//LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP


	for (uint8_t  j=0 ; j< 13 ; j++ )
	{
		Tref->Current_PSP-- ;
		*(Tref->Current_PSP)  = 0 ;

	}


}
MYRTOS_errorID MYRTOS_CreateTask(Task_Ref* Tref)
{
	MYRTOS_errorID Error = NOError ;

	//Create Its Own PSP Stack
	//Check task Stack Size exceed The PSP Stack
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator ;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;

	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-

	if(Tref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		return Task_exceeded_StackSize ;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator = (Tref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack(Tref);


	//Task State Update ->Suspend
	Tref->TaskState = Suspend ;

	//Updater Scheduler Table
	OS_Control.OSTasks[OS_Control.NoOfActiveTasks] = Tref ;
	OS_Control.NoOfActiveTasks++ ;

	return Error ;
}

//Handler
void bubbleSort()
{
	unsigned int i, j , n;
	Task_Ref* temp ;
	n = OS_Control.NoOfActiveTasks ;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.OSTasks[j]->Priority > OS_Control.OSTasks[j + 1]->Priority)
			{
				temp = OS_Control.OSTasks[j] ;
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1 ] ;
				OS_Control.OSTasks[j + 1] = temp ;
			}
}

void MYTROS_Update_Sechduler_Table()
{

	Task_Ref* temp =NULL ;
	Task_Ref* Ptask ;
	uint8_t i =0, j = 0 ;

	//1- bubble sort SchTable OS_Control-> OSTASKS[100] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp) != FIFO_EMPTY);
	//3- update ready queue

	while(i<OS_Control.NoOfActiveTasks)
	{
		Ptask = OS_Control.OSTasks[i] ;

		if(OS_Control.OSTasks[j]->Priority == Ptask->Priority)
		{
			if(Ptask->TaskState != Suspend)
			{
				Ptask->TaskState = Ready ;
				FIFO_enqueue(&Ready_QUEUE, Ptask);

			}
			else
			{
				j++ ;
			}
		}
		else
		{
			break ;
		}
		i++ ;
	}
}

__attribute ((naked)) void PendSV_Handler()
{
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP (Pointer) tp store (R4 to R11)
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r4 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r5 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r6 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r7 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r8 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r9 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r10 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("MOV %0,r11 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );

	//save the current Value of PSP
	//already saved in Current_PSP



	//====================================
	//Restore the Context of the Next Task
	//====================================
	if (OS_Control.NextTask != NULL){
		OS_Control.CurrentTask = OS_Control.NextTask ;
		OS_Control.NextTask = NULL ;
	}

	__asm volatile("MOV r11,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r10,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r9,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r8,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r7,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r6,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r5,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("MOV r4,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;

	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	__asm volatile("BX LR");

}

//Handler Mode
void Decide_WhatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if (Ready_QUEUE.counter == 0 && OS_Control.CurrentTask->TaskState != Suspend) //FIFO_EMPTY
	{
		OS_Control.CurrentTask->TaskState = Running ;
		//add the current task again(round robin)
		FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask ;
	}else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running ;
		//update Ready queue (to keep round robin Algo. happen)
		if ((OS_Control.CurrentTask->Priority == OS_Control.NextTask->Priority )&&(OS_Control.CurrentTask->TaskState != Suspend))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState = Ready ;
		}
	}
}

//Handler Mode
void MYRTOS_SVC_Services(int* StackFramePointer)
{
	//OS_SVC_Stack -> r0 ->stackFramePointer
	//OS_SVC_Stack r0 ,r1,r2,r3 ,r12,LR ,PC ,XPSR

	uint8_t SVC_number ;

	SVC_number = *((uint8_t*)(((uint8_t*)StackFramePointer[6])-2));


	switch(SVC_number)
	{
	case SVC_Activatetask:
	case SVC_terminateTask:
		//Update Scheduler Table , Ready Queue
		MYTROS_Update_Sechduler_Table();
		//OS is Running State
		if(OS_Control.OSModeID == OSRunning)
		{
			if(strcmp((char *)OS_Control.CurrentTask->TaskName , "idleTask") != 0)
			{
				//Decide what next
				Decide_WhatNext();

				//trigger OS_PendSV (Switch Context/Restore)
				trigger_OS_PendSV();

			}
		}
		break ;

	case SVC_TaskWaitingTime:
		MYTROS_Update_Sechduler_Table();
		break ;
	}
}

void MYRTOS_SVC_Set(SVC_ID ID)
{

	switch(ID)
	{
	case SVC_Activatetask:

		__asm("SVC #0X00");
		break ;

	case SVC_terminateTask:
		__asm("SVC #0X01");
		break ;

	case SVC_TaskWaitingTime :
		__asm("SVC #0X02");
		break ;
	case SVC_AquireMutex:
		__asm("SVC #0x03");  //Assignment Task
		break;
	case SVC_ReleaseMutex:
		__asm("SVC #0x04"); //Assignment Task
		break;
	}

}

void MYRTOS_ActivateTask(Task_Ref * Tref)
{
	Tref->TaskState = Waiting ;
	MYRTOS_SVC_Set(SVC_Activatetask);

}
void MYRTOS_TerminateTask(Task_Ref * Tref)
{
	Tref->TaskState = Suspend ;
	MYRTOS_SVC_Set(SVC_terminateTask);
}

void MYRTOS_TaskWait(uint32_t NOFTICKS , Task_Ref * SelfTRef)
{
	SelfTRef->TimingWaiting.Blocking = enable ;
	SelfTRef->TimingWaiting.Ticks_Count = NOFTICKS ;
	//Task Should be blocked
	SelfTRef->TaskState = Suspend ;
	//to be suspended immediately
	MYRTOS_SVC_Set(SVC_terminateTask);
}

void MYRTOS_STARTOS()
{
	OS_Control.OSModeID  =OSRunning ;

	//Set Default "Current Task =Idle Task"

	OS_Control.CurrentTask = &MYRTOS_idleTask ;

	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_idleTask);

	//Start Ticker
	Start_Ticker(); // 1ms

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);

	OS_SWITCH_To_SP_PSP;
	OS_SWITCH_To_Unprivilage;

	OS_Control.CurrentTask->P_TaskEntry() ;
}

//The function iterates through the array of active tasks (OS_Control.OSTasks),
//		checks if the task state is Suspend (i.e. it's blocked), and if the task's timing wait
//				(OS_Control.OSTasks[i]->TimingWaiting) is enabled, decrements the wait ticks count.
//				If the count reaches 1, the task's blocking is disabled and its state is set to Waiting.

void MYRTOS_Update_TasksWaitingTime()
{
	for(int i = 0 ;i< OS_Control.NoOfActiveTasks ; i++ )
	{
		if(OS_Control.OSTasks[i]->TaskState == Suspend )
		{
			if(OS_Control.OSTasks[i]->TimingWaiting.Blocking == enable)
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count-- ;
				if(OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count == 1)
				{
					OS_Control.OSTasks[i]->TimingWaiting.Blocking = disable ;
					OS_Control.OSTasks[i]->TaskState = Waiting ;
					MYRTOS_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}

MYRTOS_errorID MYRTOS_AcquireMutex(Mutex_ref* Mref , Task_Ref* Tref)
{
	if(Mref->CurrentTUser == NULL)
	{
		Mref->CurrentTUser = Tref ;
	}
	else
	{
		if(Mref->NextTUser == NULL)
		{
			Mref->NextTUser =Tref ;

			//Move to suspend state until be released
			Tref->TaskState = Suspend ;

			//to be suspend immediately
			MYRTOS_SVC_Set(SVC_terminateTask);

		}
		else
		{
			return MutexisReacedToMaxNumberOfUsers ;
		}
	}
	return NOError ;
}
void MYRTOS_ReleaseMutex(Mutex_ref* Mref)
{
	if(Mref->CurrentTUser != NULL)
	{
		Mref->CurrentTUser = Mref->NextTUser ;
		Mref->NextTUser = NULL ;
		Mref->CurrentTUser->TaskState = Waiting ;
		MYRTOS_SVC_Set(SVC_Activatetask);
	}
}
