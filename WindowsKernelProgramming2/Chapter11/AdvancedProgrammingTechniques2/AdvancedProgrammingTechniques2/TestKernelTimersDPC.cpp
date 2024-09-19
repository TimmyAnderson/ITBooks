//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersDPC.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DPC MUSI byt vytvorena ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este DPC ma REQUEST v QUEUE, doslo by k BUGCHECK.
KDPC															KernelTimersDPCDPC;
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersDPCTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersDPCDeferredProcedureCall(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING DPC ROUTINE [%s] !!! DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersDPC(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvori sa DPC.
		KeInitializeDpc(&KernelTimersDPCDPC,KernelTimersDPCDeferredProcedureCall,nullptr);

		// !!! Inicializuje sa TIMER ako NOTIFICATION TIMER.
		KeInitializeTimerEx(&KernelTimersDPCTimer,TIMER_TYPE::NotificationTimer);

		{
			BOOLEAN												TimerSignaled=KeReadStateTimer(&KernelTimersDPCTimer);

			if (TimerSignaled==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is SINGALED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is NOT SINGALED.\n",FunctionName));
			}
		}

		{
			LARGE_INTEGER										DueTime;

			DueTime.QuadPart=(-10000LL*1000);

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersDPCTimer,DueTime,0,&KernelTimersDPCDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
			}
		}

		{
			BOOLEAN												TimerSignaled=KeReadStateTimer(&KernelTimersDPCTimer);

			if (TimerSignaled==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is SINGALED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is NOT SINGALED.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER a DPC.
		CHelpers::Sleep(2000);

		{
			BOOLEAN												TimerSignaled=KeReadStateTimer(&KernelTimersDPCTimer);

			if (TimerSignaled==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is SINGALED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is NOT SINGALED.\n",FunctionName));
			}
		}

		// !!! Len pre istotu sa zastavi TIMER, aj ked teraz uz TIMER by nemal byt nastaveny.
		KeCancelTimer(&KernelTimersDPCTimer);

		// !!! Len pre istotu sa vycisti DPC, aj ked teraz uz DPC by nemala obsahovat ziadne REQUESTS.
		KeRemoveQueueDpc(&KernelTimersDPCDPC);

		{
			BOOLEAN												TimerSignaled=KeReadStateTimer(&KernelTimersDPCTimer);

			if (TimerSignaled==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is SINGALED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER is NOT SINGALED.\n",FunctionName));
			}
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------