//----------------------------------------------------------------------------------------------------------------------
#include "TestExtendedTimersNoWake.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersNoWakeCallback(PEX_TIMER Timer, PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Timer);

	const char*													FunctionName=__FUNCTION__;

	const char*													ID=static_cast<char*>(Context);

	KdPrint(("++++++++++ DRIVER EXECUTING TIMER CALLBACK ROUTINE [%s]. ID [%s].\n",FunctionName,ID));
}
//----------------------------------------------------------------------------------------------------------------------
void ExtendedTimersNoWakeDeleteCallback(PVOID Context)
{
	// !!! CODE sa vykonava v IRQL [DISPATCH_LEVEL].

	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("---------- DRIVER EXECUTING TIMER DELETE CALLBACK ROUTINE [%s].\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExtendedTimersNoWake(DEVICE_OBJECT* DeviceObject, IRP* Irp)
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

		// !!! Vytvara sa EXTENDED TIMER.
		// !!! Nepouzitie FLAG [EX_TIMER_HIGH_RESOLUTION] znamena, ze TIMER bude LOW RESOLUTION TIMER.
		// !!! EXTENDED TIMER je SYNCHRONIZATION TIMER.
		// !!! FLAG [EX_TIMER_NO_WAKE] nastavi EXTENDED TIMER na NO WAKE TIMER.
		PEX_TIMER												Timer1=ExAllocateTimer(ExtendedTimersNoWakeCallback,ID1,EX_TIMER_NO_WAKE);

		if (Timer1!=nullptr)
		{
			// !!! Vytvara sa EXTENDED TIMER.
			// !!! Nepouzitie FLAG [EX_TIMER_HIGH_RESOLUTION] znamena, ze TIMER bude LOW RESOLUTION TIMER.
			// !!! EXTENDED TIMER je SYNCHRONIZATION TIMER.
			// !!! FLAG [EX_TIMER_NO_WAKE] nastavi EXTENDED TIMER na NO WAKE TIMER.
			PEX_TIMER											Timer2=ExAllocateTimer(ExtendedTimersNoWakeCallback,ID2,EX_TIMER_NO_WAKE);

			if (Timer2!=nullptr)
			{
				// !!! Vytvara sa EXTENDED TIMER.
				// !!! Nepouzitie FLAG [EX_TIMER_HIGH_RESOLUTION] znamena, ze TIMER bude LOW RESOLUTION TIMER.
				// !!! EXTENDED TIMER je SYNCHRONIZATION TIMER.
				// !!! FLAG [EX_TIMER_NO_WAKE] nastavi EXTENDED TIMER na NO WAKE TIMER.
				PEX_TIMER										Timer3=ExAllocateTimer(ExtendedTimersNoWakeCallback,ID3,EX_TIMER_NO_WAKE);

				if (Timer3!=nullptr)
				{
					EXT_SET_PARAMETERS							SetTimerParameters1;

					ExInitializeSetTimerParameters(&SetTimerParameters1);

					// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
					SetTimerParameters1.NoWakeTolerance=10000LL*1000;

					EXT_SET_PARAMETERS							SetTimerParameters2;

					ExInitializeSetTimerParameters(&SetTimerParameters2);

					// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
					SetTimerParameters2.NoWakeTolerance=10000LL*1000;

					EXT_SET_PARAMETERS							SetTimerParameters3;

					ExInitializeSetTimerParameters(&SetTimerParameters3);

					// !!!!! TOLERANCE sa nastavi na 1 SEKUNDU.
					SetTimerParameters3.NoWakeTolerance=10000LL*1000;

					// !!! Nastavi sa EXPIRATION TIME.
					// !!! Daju sa rozdielne TIMEOUTS, aby sa simulovala cinnost NoWake TIMERS.
					BOOLEAN										TimerCancelledInSetTime1=ExSetTimer(Timer1,-10000LL*2000,0,&SetTimerParameters1);
			
					if (TimerCancelledInSetTime1==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 1 was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 1 was SET.\n",FunctionName));
					}

					// !!! Nastavi sa EXPIRATION TIME.
					// !!! Daju sa rozdielne TIMEOUTS, aby sa simulovala cinnost NoWake TIMERS.
					BOOLEAN										TimerCancelledInSetTime2=ExSetTimer(Timer2,-10000LL*2200,0,&SetTimerParameters2);
			
					if (TimerCancelledInSetTime2==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 2 was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 2 was SET.\n",FunctionName));
					}

					// !!! Nastavi sa EXPIRATION TIME.
					// !!! Daju sa rozdielne TIMEOUTS, aby sa simulovala cinnost NoWake TIMERS.
					BOOLEAN										TimerCancelledInSetTime3=ExSetTimer(Timer3,-10000LL*2400,0,&SetTimerParameters3);
			
					if (TimerCancelledInSetTime3==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 3 was SET. EXPIRATION TIME was RESET.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 3 was SET.\n",FunctionName));
					}

					PVOID										Object[]{Timer1,Timer2,Timer3};
					constexpr ULONG								Count=(sizeof(Object)/sizeof(Object[0]));
					PLARGE_INTEGER								Timeout=nullptr;
					KWAIT_BLOCK									WaitBlockArray[Count];

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

					EXT_DELETE_PARAMETERS						DeleteParameters3;

					ExInitializeDeleteTimerParameters(&DeleteParameters3);

					DeleteParameters3.DeleteCallback=ExtendedTimersNoWakeDeleteCallback;
					DeleteParameters3.DeleteContext=nullptr;

					// !!! Uvolni sa HIGH RESOLUTION TIMER.
					BOOLEAN										TimerCancelledInDelete3=ExDeleteTimer(Timer3,TRUE,TRUE,&DeleteParameters3);

					if (TimerCancelledInDelete3==TRUE)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 3 was DELETED. TIMER was CANCELLED.\n",FunctionName));
					}
					else
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 3 was DELETED. TIMER was NOT CANCELLED.\n",FunctionName));
					}
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE TIMER 3 with ERROR CODE [%lX].\n",FunctionName,Status));
				}

				EXT_DELETE_PARAMETERS							DeleteParameters2;

				ExInitializeDeleteTimerParameters(&DeleteParameters2);

				DeleteParameters2.DeleteCallback=ExtendedTimersNoWakeDeleteCallback;
				DeleteParameters2.DeleteContext=nullptr;

				// !!! Uvolni sa HIGH RESOLUTION TIMER.
				BOOLEAN											TimerCancelledInDelete2=ExDeleteTimer(Timer2,TRUE,TRUE,&DeleteParameters2);

				if (TimerCancelledInDelete2==TRUE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 2 was DELETED. TIMER was CANCELLED.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 2 was DELETED. TIMER was NOT CANCELLED.\n",FunctionName));
				}
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE TIMER 2 with ERROR CODE [%lX].\n",FunctionName,Status));
			}


			EXT_DELETE_PARAMETERS								DeleteParameters1;

			ExInitializeDeleteTimerParameters(&DeleteParameters1);

			DeleteParameters1.DeleteCallback=ExtendedTimersNoWakeDeleteCallback;
			DeleteParameters1.DeleteContext=nullptr;

			// !!! Uvolni sa HIGH RESOLUTION TIMER.
			BOOLEAN												TimerCancelledInDelete1=ExDeleteTimer(Timer1,TRUE,TRUE,&DeleteParameters1);

			if (TimerCancelledInDelete1==TRUE)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 1 was DELETED. TIMER was CANCELLED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - TIMER 1 was DELETED. TIMER was NOT CANCELLED.\n",FunctionName));
			}
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE TIMER 1 with ERROR CODE [%lX].\n",FunctionName,Status));
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------