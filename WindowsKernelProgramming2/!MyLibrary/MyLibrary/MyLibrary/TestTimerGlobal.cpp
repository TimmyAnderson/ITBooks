//----------------------------------------------------------------------------------------------------------------------
#include "TestTimerGlobal.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CTimerGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTimerGlobal													TimerGlobalTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TimerGlobalTimerCallback(PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	const char*													FunctionName=__FUNCTION__;
	const char*													TimerName=static_cast<const char*>(Context);

	KdPrint(("++++++++++ DRIVER EXECUTING TIMER [%s] CALLBACK ROUTINE [%s].\n",TimerName,FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TimerGlobalTimerDeleteCallback(PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	const char*													FunctionName=__FUNCTION__;
	const char*													TimerName=static_cast<const char*>(Context);

	KdPrint(("---------- DRIVER EXECUTING TIMER [%s] DELETE CALLBACK ROUTINE [%s].\n",TimerName,FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestTimerGlobal(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		BOOLEAN													TimerCreated=TimerGlobalTimer.Init(TimerGlobalTimerCallback,TimerGlobalTimerDeleteCallback,ETimerAttributes::E_TIMER_HIGH_RESOLUTION,PVOID("MY TIMER"));

		if (TimerCreated==TRUE)
		{
			{
				BOOLEAN											TimerCancelledInSetTime=TimerGlobalTimer.SetTimer(-10000*2000);

				if (TimerCancelledInSetTime==TRUE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
				}

				KeWaitForSingleObject(TimerGlobalTimer.GetTimer(),KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);
			}

			{
				BOOLEAN											TimerCancelledInSetTime=TimerGlobalTimer.SetTimer(-10000*2000,10000*1000);

				if (TimerCancelledInSetTime==TRUE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
				}
			}

			CHelpers::Sleep(10000);

			BOOLEAN												TimerCancelledInCancel=TimerGlobalTimer.CancelTimer();

			if (TimerCancelledInCancel==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was CANCELLED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was NOT CANCELLED.\n",FunctionName));
			}

			// !!! Uvolni sa HIGH RESOLUTION TIMER.
			BOOLEAN												TimerCancelledInDelete=TimerGlobalTimer.Destroy(TRUE,TRUE);

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

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------