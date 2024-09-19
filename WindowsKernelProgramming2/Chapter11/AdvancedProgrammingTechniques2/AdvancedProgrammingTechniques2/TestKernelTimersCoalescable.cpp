//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersCoalescable.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DPC MUSI byt vytvorena ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este DPC ma REQUEST v QUEUE, doslo by k BUGCHECK.
KDPC															KernelTimersCoalescableDPC1;
KDPC															KernelTimersCoalescableDPC2;
KDPC															KernelTimersCoalescableDPC3;
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersCoalescableTimer1;
KTIMER															KernelTimersCoalescableTimer2;
KTIMER															KernelTimersCoalescableTimer3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersCoalescableDeferredProcedureCall(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	const char*													ID=static_cast<char*>(DeferredContext);

	KdPrint(("---------- DRIVER EXECUTING DPC ROUTINE [%s] !!! ID [%s] DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,ID,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersCoalescable(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		static char												ID1[]{"111"};
		static char												ID2[]{"222"};
		static char												ID3[]{"333"};

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		// !!! Vytvoria sa DPC.
		KeInitializeDpc(&KernelTimersCoalescableDPC1,KernelTimersCoalescableDeferredProcedureCall,ID1);
		KeInitializeDpc(&KernelTimersCoalescableDPC2,KernelTimersCoalescableDeferredProcedureCall,ID2);
		KeInitializeDpc(&KernelTimersCoalescableDPC3,KernelTimersCoalescableDeferredProcedureCall,ID3);

		// !!! Inicializuju sa TIMERS.
		KeInitializeTimerEx(&KernelTimersCoalescableTimer1,TIMER_TYPE::NotificationTimer);
		KeInitializeTimerEx(&KernelTimersCoalescableTimer2,TIMER_TYPE::NotificationTimer);
		KeInitializeTimerEx(&KernelTimersCoalescableTimer3,TIMER_TYPE::NotificationTimer);

		LARGE_INTEGER											DueTime1;
		LARGE_INTEGER											DueTime2;
		LARGE_INTEGER											DueTime3;

		// !!! Daju sa rozdielne TIMEOUTS, aby sa simulovala cinnost COALESCABLE TIMERS.
		DueTime1.QuadPart=(-10000LL*2000);
		DueTime2.QuadPart=(-10000LL*2100);
		DueTime3.QuadPart=(-10000LL*2200);

		// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
		KeSetCoalescableTimer(&KernelTimersCoalescableTimer1,DueTime1,0,1000,&KernelTimersCoalescableDPC1);

		// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
		KeSetCoalescableTimer(&KernelTimersCoalescableTimer2,DueTime2,0,1000,&KernelTimersCoalescableDPC2);

		// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
		KeSetCoalescableTimer(&KernelTimersCoalescableTimer3,DueTime3,0,1000,&KernelTimersCoalescableDPC3);

		PVOID												Object[]{&KernelTimersCoalescableTimer1,&KernelTimersCoalescableTimer2,&KernelTimersCoalescableTimer3};
		constexpr ULONG										Count=(sizeof(Object)/sizeof(Object[0]));
		PLARGE_INTEGER										Timeout=nullptr;
		KWAIT_BLOCK											WaitBlockArray[Count];

		// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
		Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,WaitBlockArray);

		if (Status==STATUS_SUCCESS)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMERS FINISHED.\n",FunctionName));
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for TIMERS with ERROR CODE [%lX].\n",FunctionName,Status));
		}

		// !!! Len pre istotu sa zastavia TIMERS, aj ked teraz uz TIMERS by nemali byt nastavene.
		KeCancelTimer(&KernelTimersCoalescableTimer1);
		KeCancelTimer(&KernelTimersCoalescableTimer2);
		KeCancelTimer(&KernelTimersCoalescableTimer3);

		// !!! Len pre istotu sa vycistia DPC, aj ked teraz uz DPC by nemali obsahovat ziadne REQUESTS.
		KeRemoveQueueDpc(&KernelTimersCoalescableDPC1);
		KeRemoveQueueDpc(&KernelTimersCoalescableDPC2);
		KeRemoveQueueDpc(&KernelTimersCoalescableDPC3);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------