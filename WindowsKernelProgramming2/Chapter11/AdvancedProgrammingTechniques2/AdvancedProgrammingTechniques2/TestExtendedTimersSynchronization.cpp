//----------------------------------------------------------------------------------------------------------------------
#include "TestExtendedTimersSynchronization.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersSynchronizationTimerCallback(PEX_TIMER Timer, PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Timer);
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("++++++++++ DRIVER EXECUTING TIMER CALLBACK ROUTINE [%s].\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersSynchronizationTimerDeleteCallback(PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING TIMER DELETE CALLBACK ROUTINE [%s].\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersSynchronizationThread1(PVOID StartContext)
{
	PEX_TIMER													Timer=static_cast<PEX_TIMER>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	NTSTATUS													Status=KeWaitForSingleObject(Timer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 WOKE UP because TIMER is SIGNALED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FAILED to WAIT for TIMER with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersSynchronizationThread2(PVOID StartContext)
{
	PEX_TIMER													Timer=static_cast<PEX_TIMER>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	NTSTATUS													Status=KeWaitForSingleObject(Timer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 WOKE UP because TIMER is SIGNALED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FAILED to WAIT for TIMER with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersSynchronizationThread3(PVOID StartContext)
{
	PEX_TIMER													Timer=static_cast<PEX_TIMER>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 STARTED.\n",FunctionName));

	NTSTATUS													Status=KeWaitForSingleObject(Timer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 WOKE UP because TIMER is SIGNALED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FAILED to WAIT for TIMER with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExtendedTimersSynchronization(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvara sa EXTENDED TIMER.
		// !!! Pouzitie FLAG [EX_TIMER_HIGH_RESOLUTION] znamena, ze TIMER bude HIGH RESOLUTION TIMER.
		// !!! EXTENDED TIMER je SYNCHRONIZATION TIMER.
		PEX_TIMER												Timer=ExAllocateTimer(ExtendedTimersSynchronizationTimerCallback,nullptr,EX_TIMER_HIGH_RESOLUTION);

		if (Timer!=nullptr)
		{
			EXT_SET_PARAMETERS									SetTimerParameters;

			ExInitializeSetTimerParameters(&SetTimerParameters);

			PETHREAD											ThreadObject1=nullptr;
			PETHREAD											ThreadObject2=nullptr;
			PETHREAD											ThreadObject3=nullptr;

			do
			{
				Status=CHelpers::CreateThread(DeviceObject,"111",ExtendedTimersSynchronizationThread1,Timer,&ThreadObject1);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"222",ExtendedTimersSynchronizationThread2,Timer,&ThreadObject2);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"333",ExtendedTimersSynchronizationThread3,Timer,&ThreadObject3);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 3 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				CHelpers::Sleep(500);

				{
					// !!! Nastavi sa EXPIRATION TIME.
					BOOLEAN										TimerCancelledInSetTime=ExSetTimer(Timer,-10000LL*1000,0,&SetTimerParameters);
			
					if (TimerCancelledInSetTime==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
					}
				}

				CHelpers::Sleep(1500);

				{
					// !!! Nastavi sa EXPIRATION TIME.
					BOOLEAN										TimerCancelledInSetTime=ExSetTimer(Timer,-10000LL*1000,0,&SetTimerParameters);
			
					if (TimerCancelledInSetTime==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
					}
				}

				CHelpers::Sleep(1500);

				{
					// !!! Nastavi sa EXPIRATION TIME.
					BOOLEAN										TimerCancelledInSetTime=ExSetTimer(Timer,-10000LL*1000,0,&SetTimerParameters);
			
					if (TimerCancelledInSetTime==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
					}
				}

				PVOID											Object[]{ThreadObject1,ThreadObject2,ThreadObject3};
				constexpr ULONG									Count=(sizeof(Object)/sizeof(Object[0]));
				PLARGE_INTEGER									Timeout=nullptr;
				KWAIT_BLOCK										WaitBlockArray[Count];

				// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
				Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,WaitBlockArray);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREADS FINISHED.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREADS with ERROR CODE [%lX].\n",FunctionName,Status));
				}
			}
			while(false);

			if (ThreadObject3!=nullptr)
			{
				ObDereferenceObject(ThreadObject3);
				ThreadObject3=nullptr;
			}

			if (ThreadObject2!=nullptr)
			{
				ObDereferenceObject(ThreadObject2);
				ThreadObject2=nullptr;
			}

			if (ThreadObject1!=nullptr)
			{
				ObDereferenceObject(ThreadObject1);
				ThreadObject1=nullptr;
			}

			EXT_DELETE_PARAMETERS								DeleteParameters;

			ExInitializeDeleteTimerParameters(&DeleteParameters);

			DeleteParameters.DeleteCallback=ExtendedTimersSynchronizationTimerDeleteCallback;
			DeleteParameters.DeleteContext=nullptr;

			// !!! Uvolni sa HIGH RESOLUTION TIMER.
			BOOLEAN												TimerCancelledInDelete=ExDeleteTimer(Timer,TRUE,TRUE,&DeleteParameters);

			if (TimerCancelledInDelete==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was DELETED. TIMER was CANCELLED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was DELETED. TIMER was NOT CANCELLED.\n",FunctionName));
			}
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE TIMER with ERROR CODE [%lX].\n",FunctionName,Status));
		}

		/*



		*/



		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------