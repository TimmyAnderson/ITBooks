//----------------------------------------------------------------------------------------------------------------------
#include "TestKernelTimersResolution.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DPC MUSI byt vytvorena ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este DPC ma REQUEST v QUEUE, doslo by k BUGCHECK.
KDPC															KernelTimersResolutionDPC;
// !!!!! TIMER MUSI byt vytvoreny ako GLOBAL VARIABLE, a NIE ako LOCAL VARIABLE, inak by hrozilo, ze ak dojde k precasnemu skonceniu FUNCTION, ktora obsahuje LOCAL VARIABLE ak este TIMER ma byt vykonany, doslo by k BUGCHECK.
KTIMER															KernelTimersResolutionTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void KernelTimersResolutionDeferredProcedureCall(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING DPC ROUTINE [%s] !!! DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestKernelTimersResolution(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		ULONG													MaximumTime;
		ULONG													MinimumTime;
		ULONG													CurrentTime;

		ExQueryTimerResolution(&MaximumTime,&MinimumTime,&CurrentTime);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - MINIMUM RESOLUTION [%lu] MAXIMUM RESOLUTION [%lu] CURRENT RESOLUTION [%lu].\n",FunctionName,(MinimumTime/10),(MaximumTime/10),(CurrentTime/10)));

		// !!! Vytvori sa DPC.
		KeInitializeDpc(&KernelTimersResolutionDPC,KernelTimersResolutionDeferredProcedureCall,nullptr);

		// !!! Inicializuje sa TIMER ako SYNCHRONIZATION TIMER.
		KeInitializeTimerEx(&KernelTimersResolutionTimer,TIMER_TYPE::SynchronizationTimer);

		// SET TIMER 1.

		{
			LARGE_INTEGER										DueTime;

			// !!! Nastavi sa TIME na 1 SECOND.
			DueTime.QuadPart=-(10000*1);

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersResolutionTimer,DueTime,0,&KernelTimersResolutionDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER.
		KeWaitForSingleObject(&KernelTimersResolutionTimer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		// SET TIMER 2.

		{
			// !!!!! 2. PARAMETER nastaveny na VALUE [TRUE] znamena, ze sa zmeni RESOLUTION.
			ULONG												CurrentResolution=ExSetTimerResolution(MinimumTime*2,TRUE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - CURRENT RESOLUTION [%lu].\n",FunctionName,(CurrentResolution/10)));
		}

		ExQueryTimerResolution(&MaximumTime,&MinimumTime,&CurrentTime);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - MINIMUM RESOLUTION [%lu] MAXIMUM RESOLUTION [%lu] CURRENT RESOLUTION [%lu].\n",FunctionName,(MinimumTime/10),(MaximumTime/10),(CurrentTime/10)));

		{
			LARGE_INTEGER										DueTime;

			// !!! Nastavi sa TIME na 2 nasobok MINIMUM RESOLUTION TIME.
			DueTime.QuadPart=-(LONGLONG(MinimumTime*2));

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersResolutionTimer,DueTime,0,&KernelTimersResolutionDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER.
		KeWaitForSingleObject(&KernelTimersResolutionTimer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		// SET TIMER 3.

		{
			// !!!!! 2. PARAMETER nastaveny na VALUE [TRUE] znamena, ze sa zmeni RESOLUTION.
			ULONG												CurrentResolution=ExSetTimerResolution(MinimumTime,TRUE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - CURRENT RESOLUTION [%lu].\n",FunctionName,(CurrentResolution/10)));
		}

		ExQueryTimerResolution(&MaximumTime,&MinimumTime,&CurrentTime);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - MINIMUM RESOLUTION [%lu] MAXIMUM RESOLUTION [%lu] CURRENT RESOLUTION [%lu].\n",FunctionName,(MinimumTime/10),(MaximumTime/10),(CurrentTime/10)));

		{
			LARGE_INTEGER										DueTime;

			// !!! Nastavi sa TIME na MINIMUM RESOLUTION TIME.
			DueTime.QuadPart=-(LONGLONG(MinimumTime));

			BOOLEAN												TimerWasSet=KeSetTimerEx(&KernelTimersResolutionTimer,DueTime,0,&KernelTimersResolutionDPC);

			if (TimerWasSet==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS (ALREADY) SET.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER WAS SET.\n",FunctionName));
			}
		}

		// !!!!! Pocka sa na skoncenie TIMER.
		KeWaitForSingleObject(&KernelTimersResolutionTimer,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		{
			// !!!!! 2. PARAMETER nastaveny na VALUE [FALSE] znamena, je dekrementovany COUNTER obsahujuci pocet volani FUNCTION [ExSetTimerResolution()] a ked COUNTER klesne na VALUE [0], tak sa RESOLUTION vrati na povodnu VALUE.
			ULONG												CurrentResolution=ExSetTimerResolution(0,FALSE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - CURRENT RESOLUTION [%lu].\n",FunctionName,(CurrentResolution/10)));
		}

		ExQueryTimerResolution(&MaximumTime,&MinimumTime,&CurrentTime);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - MINIMUM RESOLUTION [%lu] MAXIMUM RESOLUTION [%lu] CURRENT RESOLUTION [%lu].\n",FunctionName,(MinimumTime/10),(MaximumTime/10),(CurrentTime/10)));

		{
			// !!!!! 2. PARAMETER nastaveny na VALUE [FALSE] znamena, je dekrementovany COUNTER obsahujuci pocet volani FUNCTION [ExSetTimerResolution()] a ked COUNTER klesne na VALUE [0], tak sa RESOLUTION vrati na povodnu VALUE.
			ULONG												CurrentResolution=ExSetTimerResolution(0,FALSE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - CURRENT RESOLUTION [%lu].\n",FunctionName,(CurrentResolution/10)));
		}

		ExQueryTimerResolution(&MaximumTime,&MinimumTime,&CurrentTime);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - MINIMUM RESOLUTION [%lu] MAXIMUM RESOLUTION [%lu] CURRENT RESOLUTION [%lu].\n",FunctionName,(MinimumTime/10),(MaximumTime/10),(CurrentTime/10)));

		// !!! Len pre istotu sa zastavi TIMER, aj ked teraz uz TIMER by nemal byt nastaveny.
		KeCancelTimer(&KernelTimersResolutionTimer);

		// !!! Len pre istotu sa vycisti DPC, aj ked teraz uz DPC by nemala obsahovat ziadne REQUESTS.
		KeRemoveQueueDpc(&KernelTimersResolutionDPC);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------