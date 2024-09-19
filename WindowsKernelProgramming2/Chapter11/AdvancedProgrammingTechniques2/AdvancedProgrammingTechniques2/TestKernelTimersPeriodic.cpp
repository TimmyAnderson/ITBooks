//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersPeriodic.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DPC MUSI byt vytvorena ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este DPC ma REQUEST v QUEUE, doslo by k BUGCHECK.
KDPC															KernelTimersPeriodicDPC;
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersPeriodicTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersPeriodicDeferredProcedureCall(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	// !!! CODE sa vykonava v IRQL [PASSIVE_LEVEL].

	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING DPC ROUTINE [%s] !!! DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersPeriodic(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvori sa DPC.
		KeInitializeDpc(&KernelTimersPeriodicDPC,KernelTimersPeriodicDeferredProcedureCall,nullptr);

		// !!! Inicializuje sa TIMER ako NOTIFICATION TIMER.
		KeInitializeTimerEx(&KernelTimersPeriodicTimer,TIMER_TYPE::NotificationTimer);

		{
			LARGE_INTEGER										DueTime;

			DueTime.QuadPart=(-10000LL*1000);

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersPeriodicTimer,DueTime,1000,&KernelTimersPeriodicDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER a DPC.
		CHelpers::Sleep(10000);

		// !!! Len pre istotu sa zastavi TIMER, aj ked teraz uz TIMER by nemal byt nastaveny.
		KeCancelTimer(&KernelTimersPeriodicTimer);

		// !!! Len pre istotu sa vycisti DPC, aj ked teraz uz DPC by nemala obsahovat ziadne REQUESTS.
		KeRemoveQueueDpc(&KernelTimersPeriodicDPC);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------