//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersCancelBySetTimer.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersCancelBySetTimerTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersCancelBySetTimerThread1(PVOID StartContext)
{
	PKTIMER														Timer=static_cast<PKTIMER>(StartContext);

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
void KernelTimersCancelBySetTimerThread2(PVOID StartContext)
{
	PKTIMER														Timer=static_cast<PKTIMER>(StartContext);

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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersCancelBySetTimer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Inicializuje sa TIMER ako NOTIFICATION TIMER.
		KeInitializeTimerEx(&KernelTimersCancelBySetTimerTimer,TIMER_TYPE::NotificationTimer);

		PETHREAD												ThreadObject1=nullptr;
		PETHREAD												ThreadObject2=nullptr;

		do
		{
			Status=CHelpers::CreateThread(DeviceObject,"111",KernelTimersCancelBySetTimerThread1,&KernelTimersCancelBySetTimerTimer,&ThreadObject1);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
				break;
			}

			Status=CHelpers::CreateThread(DeviceObject,"222",KernelTimersCancelBySetTimerThread2,&KernelTimersCancelBySetTimerTimer,&ThreadObject2);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
				break;
			}

			CHelpers::Sleep(500);

			{
				LARGE_INTEGER									DueTime;

				// !!! TIMEOUT je 30 sekund.
				DueTime.QuadPart=(-10000LL*30000);

				BOOLEAN											TimerWasSet=KeSetTimerEx(&KernelTimersCancelBySetTimerTimer,DueTime,0,nullptr);

				if (TimerWasSet==TRUE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
				}
			}

			CHelpers::Sleep(1000);

			{
				LARGE_INTEGER									DueTime;

				// !!! TIMEOUT je 3 sekundy.
				DueTime.QuadPart=(-10000LL*3000);

				BOOLEAN											TimerWasSet=KeSetTimerEx(&KernelTimersCancelBySetTimerTimer,DueTime,0,nullptr);

				// !!!!! Povodny TIMEOUR je CANCELLED.
				if (TimerWasSet==TRUE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
				}
			}

			PVOID												Object[]{ThreadObject1,ThreadObject2};
			constexpr ULONG										Count=(sizeof(Object)/sizeof(Object[0]));
			PLARGE_INTEGER										Timeout=nullptr;
			KWAIT_BLOCK											WaitBlockArray[Count];

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

		// !!! Len pre istotu sa zastavi TIMER, aj ked teraz uz TIMER by nemal byt nastaveny.
		KeCancelTimer(&KernelTimersCancelBySetTimerTimer);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------