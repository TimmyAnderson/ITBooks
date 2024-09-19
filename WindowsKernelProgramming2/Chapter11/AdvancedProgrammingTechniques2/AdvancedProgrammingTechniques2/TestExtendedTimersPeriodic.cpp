//----------------------------------------------------------------------------------------------------------------------
#include "TestExtendedTimersPeriodic.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersPeriodicTimerCallback(PEX_TIMER Timer, PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Timer);
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("++++++++++ DRIVER EXECUTING TIMER CALLBACK ROUTINE [%s].\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersPeriodicTimerDeleteCallback(PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING TIMER DELETE CALLBACK ROUTINE [%s].\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExtendedTimersPeriodic(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvara sa EXTENDED TIMER.
		// !!! Pouzitie FLAG [EX_TIMER_HIGH_RESOLUTION] znamena, ze TIMER bude HIGH RESOLUTION TIMER.
		// !!! EXTENDED TIMER je SYNCHRONIZATION TIMER.
		PEX_TIMER												Timer=ExAllocateTimer(ExtendedTimersPeriodicTimerCallback,nullptr,EX_TIMER_HIGH_RESOLUTION);

		if (Timer!=nullptr)
		{
			EXT_SET_PARAMETERS									SetTimerParameters;

			ExInitializeSetTimerParameters(&SetTimerParameters);

			// !!! Nastavi sa EXPIRATION TIME.
			// !!! Nastavi sa PERIOD.
			BOOLEAN												TimerCancelledInSetTime=ExSetTimer(Timer,-10000LL*2000,10000LL*1000,&SetTimerParameters);
			
			if (TimerCancelledInSetTime==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET. EXPIRATION TIME was RESET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER was SET.\n",FunctionName));
			}

			CHelpers::Sleep(10000);

			EXT_DELETE_PARAMETERS								DeleteParameters;

			ExInitializeDeleteTimerParameters(&DeleteParameters);

			DeleteParameters.DeleteCallback=ExtendedTimersPeriodicTimerDeleteCallback;
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

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------