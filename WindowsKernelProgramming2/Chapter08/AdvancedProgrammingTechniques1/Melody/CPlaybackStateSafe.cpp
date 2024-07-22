//----------------------------------------------------------------------------------------------------------------------
#include "CPlaybackStateSafe.h"
#include <ntddbeep.h>
#include "Helpers\CLocker.h"
#include "SFullNote.h"
#include "Defines.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPlaybackStateSafe::CPlaybackStateSafe(void)
	: MLockThread(), MLockList(), MHead(), MLookaside(), MCounter(), MStopEvent(), MThread(nullptr)
{
	KdPrint((DRIVER_PREFIX "CONSTRUCTOR [CPlaybackStateSafe::CPlaybackStateSafe()] CALLED.\n"));

	InitializeListHead(&MHead);

	KeInitializeSemaphore(&MCounter,0,1000);

	KeInitializeEvent(&MStopEvent,SynchronizationEvent,FALSE);

	ExInitializePagedLookasideList(&MLookaside,nullptr,nullptr,0,sizeof(SFullNote),DRIVER_TAG,0);
}
//----------------------------------------------------------------------------------------------------------------------
CPlaybackStateSafe::~CPlaybackStateSafe(void)
{
	KdPrint((DRIVER_PREFIX "DESTRUCTOR [CPlaybackStateSafe::~CPlaybackStateSafe()] CALLED.\n"));

	// !!! Zastavi sa WORKER THREAD.
	Stop();

	ExDeletePagedLookasideList(&MLookaside);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CPlaybackStateSafe::PlayMelodyThread(PVOID Context)
{
	CPlaybackStateSafe*												Object=static_cast<CPlaybackStateSafe*>(Context);

	Object->PlayMelody();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CPlaybackStateSafe::PlayMelody(void)
{
	unsigned long												HandleAsULong=HandleToULong(PsGetCurrentThreadId());

	KdPrint((DRIVER_PREFIX "WORKER THREAD STARTED - HANDLE [%lu].\n",HandleAsULong));

	PDEVICE_OBJECT												BeepDevice;
	UNICODE_STRING												BeepDeviceName=RTL_CONSTANT_STRING(DD_BEEP_DEVICE_NAME_U);
	PFILE_OBJECT												BeepFileObject;

	// !!!!! Ziska sa DEVICE OBJECT BEEP DRIVER.
	NTSTATUS													Status=IoGetDeviceObjectPointer(&BeepDeviceName,GENERIC_WRITE,&BeepFileObject,&BeepDevice);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVER_PREFIX "WORKER THREAD - FAILED to OPEN BEEP DEVICE with ERROR [0x%X].\n",Status));
		return;
	}

	PVOID														Objects[]={&MCounter,&MStopEvent};
	IO_STATUS_BLOCK												IoStatus;
	BEEP_SET_PARAMETERS											BeepParams;

	while(true)
	{
		// !!!!! Caka sa prichod EVENT (SEMAPHORE), ktory signalizuje, ze v SHARED LIST existuju NOTES na prehratie, alebo na prichod EVENT, ktory signalizuje ukoncenie WORKER THREAD.
		// !!!!! SEMAPHORE vo svojom COUNTER udrzuje pocet NOTES v SHARED LIST. Vdaka tomu, je SEMAPHORE SIGNALIZED, ak pocet [COUNTER>0], tak SEMAPHORE je SIGNALIZED kym je v SHARED LIST aspon 1 NOTE.
		Status=KeWaitForMultipleObjects(2,Objects,WaitAny,Executive,KernelMode,FALSE,nullptr,nullptr);

		// !!!!! Ak prisiel EVENT, ktory signalizuje ukoncenie WORKER THREAD, tak je WORKER THREAD okamzite ukonceny.
		if (Status==STATUS_WAIT_1)
		{
			KdPrint((DRIVER_PREFIX "WORKER THREAD - STOP EVENT SIGNALED.\n"));
			break;
		}

		LONG													SemaphoreCount=KeReadStateSemaphore(&MCounter);

		KdPrint((DRIVER_PREFIX "WORKER THREAD - SEMAPHORE COUNT [%ld].\n",SemaphoreCount));

		PLIST_ENTRY												Link;

		{
			// !!! Zabranuje RACE CONDITION, ked THREAD pridavajuci NOTES do SHARED LIST a tento WORKER THREAD vybera NOTES zo SHARED LIST.
			CLocker												Locker(MLockList);

			// !!! Vyberie sa NOTE z LINKED LIST.
			Link=RemoveHeadList(&MHead);

			// !!!!! SHARED LIST nebude NIKDY PRAZDNY, pretoze pocet NOTES v SHARED LIST je urceny SEMAPHORE COUNTER. A ked SEMAPHORE COUNTER klesne na 0 a SHARED LIST je prazdny, tak THREAD je BLOCKED.
			NT_ASSERT(Link!=&MHead);
		}

		// !!! Ziska sa POINTER na STRUCTURE, ktora obsahuje SHARED LIST LINK.
		SFullNote*												Note=CONTAINING_RECORD(Link,SFullNote,Link);

		KdPrint((DRIVER_PREFIX "WORKER THREAD - THREAD PLAYING NOTE - FREQUENCY [%lu] DURATION [%lu] REPEAT [%lu] DELAY [%u].\n",Note->Frequency,Note->Duration,Note->Repeat,Note->Delay));

		// !!! Ak je FREQUENCY nulova, tak ton znamena ticho, takze sa ho neoplati prehravat v BEEP DRIVER a namiesto toho sa spravi iba THREAD WAIT.
		if (Note->Frequency==0)
		{
			//NT_ASSERT(Note->Duration>0);

			LARGE_INTEGER										Interval;

			Interval.QuadPart=(-10000LL*Note->Duration);

			// !!! Spravi sa THREAD WAIT namiesto prehravania ticheho TONE.
			KeDelayExecutionThread(KernelMode,FALSE,&Interval);
		}
		else
		{
			BeepParams.Duration=Note->Duration;
			BeepParams.Frequency=Note->Frequency;

			int													Count=max(1,Note->Repeat);
			KEVENT												DoneEvent;

			KeInitializeEvent(&DoneEvent,SynchronizationEvent,FALSE);

			for (int Index=0;Index<Count;Index++)
			{
				// !!!!! Vytvori sa IRP pre BEEP DRIVER.
				PIRP											Irp=IoBuildDeviceIoControlRequest(IOCTL_BEEP_SET,BeepDevice,&BeepParams,sizeof(BeepParams),nullptr,0,FALSE,&DoneEvent,&IoStatus);

				if (Irp==nullptr)
				{
					KdPrint((DRIVER_PREFIX "WORKER THREAD - FAILED to ALLOCATE IRP.\n"));
					break;
				}

				NT_ASSERT(Irp->UserEvent==&DoneEvent);

				// !!!!! IRP sa odosle do BEEP DRIVER.
				Status=IoCallDriver(BeepDevice,Irp);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint((DRIVER_PREFIX "WORKER THREAD - BEEP DEVICE FAILED to PROCESS IRP with ERROR [0x%X].\n",Status));
					break;
				}

				if (Status==STATUS_PENDING)
				{
					// !!! Caka sa na dokoncenie IRP v DEEP DRIVER.
					// !!!!! Skoncenie IRP neznamena, ze ton dohral.
					KeWaitForSingleObject(&DoneEvent,Executive,KernelMode,FALSE,nullptr);
				}

				LARGE_INTEGER									Delay;

				Delay.QuadPart=(-10000LL*Note->Duration);

				// !!!!! Caka sa kym ton nie je dohraty v BEEP DRIVER.
				KeDelayExecutionThread(KernelMode,FALSE,&Delay);

				// !!! Vykona sa DELAY, ak plati CONDITION [REPEAT>1 && DELAY>0]. DELAY sa NEROBI pre posledny ton.
				if (Index<(Count-1) && Note->Delay!=0)
				{
					Delay.QuadPart=(-10000LL*Note->Delay);

					KeDelayExecutionThread(KernelMode,FALSE,&Delay);
				}
			}
		}

		// !!!!! MEMORY v ktorej bola ulozena NOTE sa vrati spat do LOOKASIDE LIST.
		ExFreeToPagedLookasideList(&MLookaside,Note);
	}

	// !!!!! Uvolni sa FILE OBJECT na DEVICE OBJECT, cim sa zaroven urovni aj DEVICE OBJECT.
	ObDereferenceObject(BeepFileObject);

	KdPrint((DRIVER_PREFIX "WORKER THREAD FINISED.\n"));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CPlaybackStateSafe::Start(PVOID IoObject, HANDLE SystemProcessHandle)
{
	HANDLE														ProcessHandle=SystemProcessHandle;

	{
		// !!!!! Zabrani sa, aby sa FUNCTION v danom case volala viac ako 1 krat.
		CLocker													Locker(MLockThread);

		{
			if (MThread!=nullptr)
			{
				return(STATUS_SUCCESS);
			}

			// !!! Vytvori THREAD a zaroven nastavi VARIABLE [MThread].
			NTSTATUS											Status=IoCreateSystemThread(IoObject,&MThread,THREAD_ALL_ACCESS,nullptr,ProcessHandle,nullptr,PlayMelodyThread,this);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint((DRIVER_PREFIX "FAILED to CREATE THREAD OBJECT with ERROR [0x%X].\n",Status));
			}

			return(Status);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void CPlaybackStateSafe::Stop(void)
{
	// !!!!! Zabrani sa, aby sa FUNCTION v danom case volala viac ako 1 krat.
	CLocker														Locker(MLockThread);

	{
		if (MThread!=nullptr)
		{
			// !!!!! Zasle sa signal THREADU, aby skoncil.
			KeSetEvent(&MStopEvent,2,FALSE);

			PVOID												Thread;

			// !!! Z HANDLE na THREAD sa ziska KERNEL OBJECT [Thread] na ktory je mozne aplikovat WAIT FUNCTIONS. Na HANDLES WAIT FUNCTIONS nie je mozne aplikovat.
			NTSTATUS											Status=ObReferenceObjectByHandle(MThread,SYNCHRONIZE,*PsThreadType,KernelMode,&Thread,nullptr);

			if (NT_SUCCESS(Status)!=false)
			{
				// !!!!! Caka sa na skoncenie THREAD.
				KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,nullptr);

				// !!! Znizi sa COUNTER KERNEL OBJECT [Thread], aby THREAD OBJECT mohol byt uvolneny.
				ObDereferenceObject(Thread);
			}
			else
			{
				KdPrint((DRIVER_PREFIX "FAILED to get THREAD OBJECT for THREAD HANDLE with ERROR [0x%X].\n",Status));
			}

			ZwClose(MThread);
			MThread=nullptr;

			KdPrint((DRIVER_PREFIX "THREAD STOPPED.\n"));
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CPlaybackStateSafe::AddNotes(const SNote* Notes, ULONG Count)
{
	KdPrint((DRIVER_PREFIX "ADD NOTES CALLED - COUNT [%lu].\n",Count));

	for (ULONG Index=0;Index<Count;Index++)
	{
		// !!! Pre kazdy NOTE z NOTE ARRAY sa alokuje MEMORY z LOOKASIDE LIST.
		SFullNote*												FullNote=(SFullNote*)ExAllocateFromPagedLookasideList(&MLookaside);

		if (FullNote==nullptr)
		{
			return(STATUS_INSUFFICIENT_RESOURCES);
		}

		memcpy(FullNote,&Notes[Index],sizeof(SNote));

		{
			// !!! Zabranuje RACE CONDITION, ked tento THREAD pridava NOTES do SHARED LIST a WORKER THREAD vybera NOTES zo SHARED LIST.
			CLocker												Locker(MLockList);

			// !!! MEMORY sa prida na koniec SHARED LIST.
			InsertTailList(&MHead,&FullNote->Link);
		}
	}

	// !!!!! Posiela sa SIGNAL do WORKER THREAD, ze v SHARED LIST su NOTES, ktore je treba prehrat.
	// !!!!! SEMAPHORE zaroven vo svojom COUNTER udrzuje pocet NOTES v SHARED LIST. Vdaka tomu, je SEMAPHORE SIGNALIZED, ak pocet [COUNTER>0], tak SEMAPHORE je SIGNALIZED kym je v SHARED LIST aspon 1 NOTE.
	KeReleaseSemaphore(&MCounter,2,Count,FALSE);

	LONG														SemaphoreCount=KeReadStateSemaphore(&MCounter);

	KdPrint((DRIVER_PREFIX "SEMAPHORE COUNT [%ld].\n",SemaphoreCount));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------