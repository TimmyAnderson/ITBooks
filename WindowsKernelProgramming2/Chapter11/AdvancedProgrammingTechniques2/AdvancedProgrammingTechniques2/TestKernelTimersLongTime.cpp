//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersDPC.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DPC MUSI byt vytvorena ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este DPC ma REQUEST v QUEUE, doslo by k BUGCHECK.
KDPC															KernelTimersLongTimeDPC;
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersLongTimeTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersLongTimeDeferredProcedureCall(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- 111111111 DRIVER EXECUTING DPC ROUTINE [%s] !!! DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,DeferredContext,SystemArgument1,SystemArgument2));

	/*
	// !!!!! CODE sluzi na testovanie ci DRIVER UNLOAD je zavolana, ak este stale je vykonavana DPC, ktoru vyvolal dany DRIVER.
	// !!!!! DRIVER UNLOAD NIE JE spusteny, az kym vsetky DPC NIE su UKONCENE.
	for(ULONG Index1=0;Index1<10;Index1++)
	{
		for(ULONG Index2=0;Index2<1000*1000*1000;Index2++)
		{
		}
	}
	*/

	KdPrint(("---------- 222222222 DRIVER EXECUTING DPC ROUTINE [%s] !!! DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersLongTime(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvori sa DPC.
		KeInitializeDpc(&KernelTimersLongTimeDPC,KernelTimersLongTimeDeferredProcedureCall,nullptr);

		// !!! Inicializuje sa TIMER ako NOTIFICATION TIMER.
		KeInitializeTimerEx(&KernelTimersLongTimeTimer,TIMER_TYPE::NotificationTimer);

		{
			LARGE_INTEGER										DueTime;

			// !!!!! Caka sa 30 sekund.
			DueTime.QuadPart=(-10000LL*30000);

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersLongTimeTimer,DueTime,0,&KernelTimersLongTimeDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET for 30 SECONDS.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER a DPC.
		CHelpers::Sleep(40000);

		// !!! Len pre istotu sa zastavi TIMER, aj ked teraz uz TIMER by nemal byt nastaveny.
		KeCancelTimer(&KernelTimersLongTimeTimer);

		// !!! Len pre istotu sa vycisti DPC, aj ked teraz uz DPC by nemala obsahovat ziadne REQUESTS.
		KeRemoveQueueDpc(&KernelTimersLongTimeDPC);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------