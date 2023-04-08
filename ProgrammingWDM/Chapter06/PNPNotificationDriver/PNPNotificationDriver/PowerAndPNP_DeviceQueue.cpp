//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
typedef struct _NOTIFY_CONTEXT
{
	// Real notification function.
	PQNOTIFYFUNC												MNotify;
	// Context argument for notification function.
	PVOID														MContext;
	// Number of busy queues.
	LONG														MCount;
} NOTIFY_CONTEXT, *PNOTIFY_CONTEXT;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
VOID NotificationCallback(PNOTIFY_CONTEXT Context);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION je volana v DISPATCH FUNCTION pri prichode noveho IRP. To sa bud SPUSTI (ak je DEVICE VOLNE), alebo sa ulozi do IRP QUEUE (ak DEVICE spracovava iny IRP).
// !!!!! Kedze FUNCTION NEVYKONAVA LOCK nad GLOBAL CANCEL LOCK, tak HOCIKEDY pocas jej behu moze byt zavolana FUNCTION IoCancelIrp(), ktora moze sposobit zmenu FIELDS [IRP.Cancel] a [IRP.CancelRoutine].
GENERICAPI VOID GENERIC_EXPORT StartPacket(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO, PIRP IRP, PDRIVER_CANCEL Cancel)
{
	KIRQL														OldIRQL;

	// Kedze sa ide pracovat s DEVQUEUE, ziska sa LOCK.
	// !!!!! EXTREMNE DOLEZITE je zmenit IRQL na DISPATCH_LEVEL, pretoze DPC volajuca StartNextPacket(), ktora TIEZ PRISTUPUJE k DEVQUEUE bezi v IRQL==DISPATCH_LEVEL a teda ak by CODE, ktory v tejto FUNCTION pracuje s DEVQUEUE NEBEZAL v IRQL==DISPATCH_LEVEL, tak by mohol byt INTERRUPTED zo strany DPC volajucej StartNextPacket() a doslo by k NARUSENIU LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.

	// Must supply a cancel routine.
	// !!! CANCEL ROUTINE by NEMAL byt na NULL, pretoze CANCELLATION logika v DEVQUEUE silne zavisi na tom, ze CANCELLATION ROUTINE je nastaveny na NON-NULL.
	ASSERT(Cancel);

	// Maybe left over from a higher level ?
	// !!! IRP by NEMAL mat nastaveny CANCEL ROUTINE, pretoze FUNCTION StartPacket() ho nastavuje explicitne.
	ASSERT(IRP->CancelRoutine==NULL);

	// If the device has been removed by surprise, complete IRP immediately. Do not pass GO. Do not collect $200.
	NTSTATUS													AbortStatus=PDQ->MAbortStatus;

	// !!!!! Ak PNP chce odstranit DRIVER z MEMORY, tak VSETKY IRP MUSIA byt co NAJSKOR ABORTED.
	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.
	if (AbortStatus!=STATUS_SUCCESS)
	{
		DbgPrint((DRIVERLOGNAME " - FUNCTION StartPacket(): IRP will be ABORTED !\n"));

		// Aborting all requests now.
		// Uvolni LOCK a obnovi povodnu hodnotu IRQL.
		KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

		// !!! Nastavi sa ABORT STATUS pre dany IRP.
		IRP->IoStatus.Status=AbortStatus;

		// !!! IRP sa ukonci, pretoze DRIVER ma byt ODSTRANENY z MEMORY a vsetky IRP musia byt co NAJSKOR ABORTED.
		IoCompleteRequest(IRP,IO_NO_INCREMENT);
	}
	// If the device is busy with another request, or if the queue has been stalled due to some PnP or power event, just put the new IRP onto the queue and set a cancel routine pointer.
	// !!! DEVICE je BUSY a IRP musi byt ulozene do IRP QUEUE.
	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.
	else if (PDQ->MCurrentIRP!=NULL || PDQ->MStallCount!=0)
	{
		// Queue this IRP.
		// (After Peretz) See if this IRP was cancelled before it got to us. If so, make sure either we or the cancel routine completes it.
		// !!! Preto HW DEVICE je BUSY a IRP ma byt ulozene do QUEUE, tak FUNCTION IoSetCancelRoutine() ATOMICKY nastavi CANCELLATION ROUTINE pre dane IRP. IRP ulozene v IRP QUEUE teda bude mat spravne nastavenu CANCELLATION ROUTINE.
		IoSetCancelRoutine(IRP,Cancel);

		// !!!!! V TOMTO MOMENTE (takisto aj MEDZI 2 PODMIENKAMI v NASLEDUJUCOM 'if' prikaze) moze FUNCTION IoCancelIrp() sposobit RESET POINTER na CANCELLATION ROUTINE na NULL.

		// !!! Ak FIELD IRP.Cancel bol nastaveny na TRUE, tak sa VYMAZE CANCELLATION ROUTINE, pretoze IRP bude OKAMZITE CANCELLED.
		// !!!!! Podmienka [IoSetCancelRoutine(IRP,NULL)!=NULL] sluzi na to, aby sa osetril stav kedy FUNCTION IoCancelIrp() uz STIHLA nastavit FIELD [IRP.Cancel] na TRUE, ale este NESTIHLA nastavit POINTER na CANCELLATION ROUTINE na NULL. Ak dojde k tejto situacii, tak sa IRP zaradi do DEVQUEUE, odkial bude neskor vybraty a uvolneny bez dalsieho spracovania. CANCELLATION ROUTINE je v tomto pripade vyvolana vo FUNCTION IoCancelIrp().
		if (IRP->Cancel!=FALSE && IoSetCancelRoutine(IRP,NULL)!=NULL)
		{
			DbgPrint((DRIVERLOGNAME " - FUNCTION StartPacket(): IRP will be CANCELLED !\n"));

			// IRP has already been cancelled.
			// Uvolni LOCK a obnovi povodnu hodnotu IRQL.
			KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

			// !!! STATUS IRP sa nastavi na CANCELLED.
			IRP->IoStatus.Status=STATUS_CANCELLED;

			// !!!!! CANCELLED IRP sa ukonci.
			IoCompleteRequest(IRP,IO_NO_INCREMENT);
		}
		else
		{
			DbgPrint((DRIVERLOGNAME " - FUNCTION StartPacket(): IRP will be QUEUED !\n"));

			// Queue IRP.
			// !!! IRP ulozi do IRP QUEUE.
			InsertTailList(&PDQ->MHead,&IRP->Tail.Overlay.ListEntry);

			// Uvolni LOCK a obnovi povodnu hodnotu IRQL.
			KeReleaseSpinLock(&PDQ->MLock,OldIRQL);
		}
	}
	// If the device is idle and not stalled, pass the IRP to the MStartIO routine associated with this queue.
	// !!! DEVICE je volne a pripravene spracovat dalsi IRP.
	// !!!!! Ak je IRP CANCELLED, tak aj napriek tomu sa spusti FUNCTION StartIo() a je ulohou tejto FUNCTION (alebo DISPATCH ROUTINE) skontrolovat nastavenie FIELD [IRP.Cancel] na TRUE a IRP co NAJSKOR UKONCIT.
	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.
	else
	{	
		DbgPrint((DRIVERLOGNAME " - FUNCTION StartPacket(): IRP will be EXECUTED !\n"));

		// Start this IRP.
		// IRP sa ulozi do MEMBER MCurrentIRP.
		PDQ->MCurrentIRP=IRP;

		// !!! Uvolni LOCK, no zaroven PONECHA [IRQL==DISPATCH_LEVEL], pretoze FUNCTION StartIo() je NUTNE volat pri [IRQL==DISPATCH_LEVEL].
		KeReleaseSpinLock(&PDQ->MLock,DISPATCH_LEVEL);

		// !!! Vyvola CUSTOM FUNCTION StartIo(), ktora ma za ulohu SPUSTI IO OPERATION na DEVICE, ktory DRIVER obsluhuje.
		(*PDQ->MStartIO)(FDO,IRP);

		// Vrati IRQL na povodnu hodnotu.
		KeLowerIrql(OldIRQL);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION je volana pri UKONCENI IRP (najcastejsie v DPC), kedy sa ma vybrat z IRP QUEUE dalsie IRP na spracovanie.
// !!!!! Kedze FUNCTION NEVYKONAVA LOCK nad GLOBAL CANCEL LOCK, tak HOCIKEDY pocas jej behu moze byt zavolana FUNCTION IoCancelIrp(), ktora moze sposobit zmenu FIELDS [IRP.Cancel] a [IRP.CancelRoutine].
GENERICAPI PIRP GENERIC_EXPORT StartNextPacket(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO)
{
	KIRQL														OldIRQL;

	// Kedze sa ide pracovat s DEVQUEUE, ziska sa LOCK a zvysi sa IRQL na DISPATCH_LEVEL.
	// !!!!! EXTREMNE DOLEZITE je zmenit IRQL na DISPATCH_LEVEL, pretoze DISPATCH ROUTINE volajuca FUNCTION StartNextPacket() , ktora TIEZ PRISTUPUJE k DEVQUEUE bezi v [IRQL==DISPATCH_LEVEL] a teda ak by CODE, ktory v tejto FUNCTION pracuje s DEVQUEUE NEBEZAL v [IRQL==DISPATCH_LEVEL], tak by mohol byt INTERRUPTED zo strany DISPATCH ROUTINE volajucej FUNCTION StartNextPacket() a doslo by k NARUSENIU LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.

	// Nullify the current IRP pointer after remembering the current one. We'll return the current IRP pointer as our return value so that a DPC routine has a way to know whether an active request got aborted.
	// !!! Vynuluje sa POINTER na CURRENT IRP.
	PIRP														CurrentIRP=(PIRP) InterlockedExchangePointer((PVOID*) &PDQ->MCurrentIRP,NULL);

	// If we just finished processing a request, set the event on which WaitForCurrentIRP() may be waiting in some other thread.
	// !!! Signalizuje sa EVENT asociovany s prave skoncenym IRP.
	if (CurrentIRP!=NULL)
	{
		// !!! Signalizuje sa EVENT asociovany s prave skoncenym IRP.
		KeSetEvent(&PDQ->MEventStop,0,FALSE);
	}

	// If someone is waiting for notification that this IRP has finished, we'll provide the notification after we release the spin lock. We shouldn't find the queue unstalled if there is a notification routine in place, by the way.
	// POINTER na NOTIFICATION FUNCTION sa ulozi do pomocnej VARIABLE, aby NOTIFICATION FUNCTION po uvolneni LOCK.
	PQNOTIFYFUNC												Notify=PDQ->MNotify;
	PVOID														NotifyContext=PDQ->MNotifyContext;

	// POINTER na NOTIFICATION FUNCTION sa odstrani.
	PDQ->MNotify=NULL;

	DbgPrint(DRIVERLOGNAME " - FUNCTION StartNextPacket(): IRP QUEUE EMPTY [%d] ABORT [%d], STALL COUNT [%d] !\n",IsListEmpty(&PDQ->MHead),PDQ->MAbortStatus,PDQ->MStallCount);

	// Start the next IRP.
	// !!!!! Prechadza sa DEVQUEUE a hlada sa PRVE IRP, ktore NIE JE CANCELLED. Zaroven sa zistuje ci nedoslo k ABORT DEVQUEUE (napriklad pri uvolneni DRIVER z PNP MANAGER), alebo ci DEVQUEUE nie je STALLED.
	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.
	while (PDQ->MStallCount==0 && PDQ->MAbortStatus==STATUS_SUCCESS && IsListEmpty(&PDQ->MHead)==FALSE)
	{
		// !!! IRP QUEUE obsahuje IRP, pricom nedoslo k ABORT, alebo IRP STALL.

		// Start next packet.
		// !!! Z IRP QUEUE sa vyberie IRP.
		PLIST_ENTRY												Next=RemoveHeadList(&PDQ->MHead);

		// Ziska sa POINTER na IRP.
		PIRP													IRPRecord=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		// (After Peretz & Hanrahan in part) Nullify the cancel pointer in this IRP. If it was already NULL, someone is trying to cancel this IRP right now. Reinitialize the link pointers so the cancel routine's call to RemoveEntryList() won't do anything harmful and look for another IRP. The cancel routine will take over as soon as we release the spin lock.
		// !!!!! Odstrani IRP, ktore uz bolo CANCELLED. IRP, ktore uz bolo CANCELLED NEMA nastavenu CANCELLATION ROUTINE.
		if (IoSetCancelRoutine(IRPRecord,NULL)==NULL)
		{
			DbgPrint((DRIVERLOGNAME " - FUNCTION StartNextPacket(): IRP was CANCELLED !\n"));

			// IRP being cancelled right now.
			// Else CancelRoutine shouldn't be NULL !
			ASSERT(IRPRecord->Cancel);

			// !!!!! HACK vdaka ktoremu FUNCTION CancelRequest() NESPOSOBI BUG CHECK pocas volania FUNCTION RemoveEntryList() pri pokuse odstranit IRP z DEVQUEUE.
			InitializeListHead(&IRPRecord->Tail.Overlay.ListEntry);

			// With "start next packet".
			continue;
		}

		PDQ->MCurrentIRP=IRPRecord;

		// !!! Uvolni SPIN LOCK, ale zaroven PONECHA [IRQL==DISPATCH_LEVEL], pretoze FUNCTION StartIo() vyzaduje, aby bola volana pri [IRQL==DISPATCH_LEVEL].
		KeReleaseSpinLockFromDpcLevel(&PDQ->MLock);

		DbgPrint(DRIVERLOGNAME " - FUNCTION StartNextPacket(): IRP will be EXECUTED !\n");

		// !!! Pre IRP vybraty z IRP QUEUE vyvola CUSTOM FUNCTION StartIo(), ktora ma za ulohu SPUSTI IO OPERATION na DEVICE, ktory DRIVER obsluhuje.
		(*PDQ->MStartIO)(FDO,IRPRecord);

		// Znizi IRQL na povodnu hodnotu.
		KeLowerIrql(OldIRQL);

		return(CurrentIRP);
	}

	DbgPrint((DRIVERLOGNAME " - FUNCTION StartNextPacket(): IRP was ABORTED, CANCELLED or QUEUE is EMPTY !\n"));

	// Uvolni LOCK a IRQL vrati na povodnu hodnotu.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	if (Notify!=NULL)
	{
		// Vyvola sa NOTIFICATION FUNCTION.
		(*Notify)(NotifyContext);
	}

	return(CurrentIRP);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION reprezentuje CANCELLATION ROUTINE, ktora je volana z FUNCTION IoCancelIrp() pri vykonavani IRP CANCELLATION.
// !!!!! FUNCTION sluzi ako PARAMETER do FUNCTION StartPacket().
// !!!!! Kedze FUNCTION NEVYKONAVA LOCK nad GLOBAL CANCEL LOCK, tak HOCIKEDY pocas jej behu moze byt zavolana FUNCTION IoCancelIrp(), ktora moze sposobit zmenu FIELDS [IRP.Cancel] a [IRP.CancelRoutine].
_IRQL_raises_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_cancel_spin_lock_)
GENERICAPI VOID GENERIC_EXPORT CancelRequest(PDEVQUEUE PDQ, PIRP IRP)
{
	KIRQL														OldIRQL=IRP->CancelIrql;

	// Release the global cancel spin lock as soon as possible.
	// !!!!! Je POVINNOSTOU KAZDEJ CANCELLATION ROUTINE UVOLNIT CANCELLATION LOCK volanim FUNCTION IoReleaseCancelSpinLock().
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	// Acquire our queue-specific queue lock. Note that we stayed at DISPATCH_LEVEL when we released the cancel spin lock.
	// !!! Kedze sa ide pristupit k DEVQUEUE, tak je NUTNE ZISKAT LOCK.
	// !!!!! Kedze aj FUNCTIONS StartPacket() a StartNextPacket() si drzia tento LOCK, CODE za volanim FUNCTION KeAcquireSpinLockAtDpcLevel() sa NEVYKONA skor ako FUNCTIONS StartPacket() a StartNextPacket() LOCK UVOLNIA.
	KeAcquireSpinLockAtDpcLevel(&PDQ->MLock);

	// !!!!! Tento CODE sa vola AZ POTOM co FUNCTIONS StartPacket() a StartNextPacket() uvolnili LOCK PDQ->MLock.

	// (After Peretz & Hanrahan) The IRP is guaranteed to be on *some* queue (maybe a degenerate one), so we unconditionally remove it and complete it.
	// !!! IRP je URCITE v DEVQUEUE a musi byt z neho ODSTRANENY.
	// !!!!! Alternativou je, ked IRP uz NIE JE v IRP QUEUE, ale v tom pripade FUNCTION StartNextPacket() nastavila FIELD [IRP->Tail.Overlay.ListEntry] tak, ze FUNCTION RemoveEntryList() NESPRAVI ZIADNU CINNOST a teda NEOSTRANI IRP z IRP QUEUE (ktore tam uz nie je).
	RemoveEntryList(&IRP->Tail.Overlay.ListEntry);

	// LOCK chraniaci DEVQUEUE je mozne uvolnit.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	// IRP nastavi na CANCELLED STATUS.
	IRP->IoStatus.Status=STATUS_CANCELLED;

	// !!! Ukonci IRP.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [READY] do STATE [STALLED].
// FUNCTION pozastavuje spracovanie IRP inkrementaciou hodnoty DEVQUEUE.MStallCount.
GENERICAPI VOID GENERIC_EXPORT StallRequests(PDEVQUEUE PDQ)
{
	// !!! Inkrementuje sa STALL COUNTER cim sa zabrani aby DEVQUEUE spustila spracovanie noveho IRP.
	InterlockedIncrement(&PDQ->MStallCount);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [READY] do STATE [STALLED].
// FUNCTION pozastavuje spracovanie IRP pre vsetky DEVQUEUES v zadanom DEVQUEUE ARRAY.
GENERICAPI VOID GENERIC_EXPORT StallAllRequests(PDEVQUEUE* Queue, ULONG NumberOfQueues)
{
	// !!! Inkrementuje sa STALL COUNTER pre vsetky DEVQUEUES cim sa zabrani aby DEVQUEUES spustili spracovanie novych IRP.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		StallRequests(Queue[Index]);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [READY] do STATE [STALLED].
// FUNCTION pozastavuje spracovanie IRP inkrementaciou hodnoty DEVQUEUE.MStallCount. FUNCTION zaroven nastavi NOTIFICATION FUNCTION v DEVQUEUE.
GENERICAPI NTSTATUS GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE PDQ, PQNOTIFYFUNC Notify, PVOID Context)
{
	NTSTATUS													Status;
	KIRQL														OldIRQL;

	// !!! Kedze FUNCTION pracuje s INTERNYM STATE DEVQUEUE musi ziskat SPIN LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!! Ak uz bola NOTIFICATION FUNCTION nastavena, FUNCTION skonci vratenim ERROR CODE.
	if (PDQ->MNotify!=NULL)
	{
		Status=STATUS_INVALID_DEVICE_REQUEST;
	}
	else
	{
		// Valid request.
		// !!! Inkrementuje sa STALL COUNTER cim sa zabrani aby DEVQUEUE spustila spracovanie noveho IRP.
		InterlockedIncrement(&PDQ->MStallCount);

		// !!! Ak IRP je prave spracovane, nastavi sa NOTIFICATION FUNCTION.
		if (PDQ->MCurrentIRP!=NULL)
		{
			// Device is busy.
			PDQ->MNotify=Notify;
			PDQ->MNotifyContext=Context;
			Status=STATUS_PENDING;
		}
		else
		{
			// Device is idle.
			Status=STATUS_SUCCESS;
		}
	}

	// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [READY] do STATE [STALLED].
// FUNCTION pozastavuje spracovanie IRP pre vsetky DEVQUEUES v zadanom DEVQUEUE ARRAY. FUNCTION zaroven nastavi NOTIFICATION FUNCTION v DEVQUEUE.
GENERICAPI NTSTATUS GENERIC_EXPORT StallAllRequestsAndNotify(PDEVQUEUE* Queue, ULONG NumberOfQueues, PQNOTIFYFUNC Notify, PVOID Context)
{
	NTSTATUS													Status;
	KIRQL														OldIRQL;
	ULONG														Index;

	// Acquire all of the queue locks. We're not worried about a deadlock because this is the only function that ever simultaneously locks more than one queue.
	KeRaiseIrql(DISPATCH_LEVEL,&OldIRQL);

	for (Index=0;Index<NumberOfQueues;++Index)
	{
		// !!! Kedze FUNCTION pracuje s INTERNYM STATE VSETKYCH DEVQUEUES musi ziskat ich SPIN LOCKS.
		KeAcquireSpinLockAtDpcLevel(&Queue[Index]->MLock);
	}

	// Examine each of the queues in a manner similar to the single-queue version of this function.
	// Number of busy devices.
	ULONG														NBusy=0;
	// Index of last busy device.
	ULONG														IBusy=0;

	// Prechadzaju sa vsetky DEVQUEUES.
	for (Index=0;Index<NumberOfQueues;++Index)
	{
		// Examine each queue.
		PDEVQUEUE												PDQ=Queue[Index];

		// !!! Ak uz bola NOTIFICATION FUNCTION nastavena, FUNCTION skonci vratenim ERROR CODE.
		if (PDQ->MNotify!=NULL)
		{
			break;
		}
		else
		{
			// Notify not pending.
			// Stall this queue.
			// !!! Inkrementuje sa STALL COUNTER cim sa zabrani aby DEVQUEUE spustila spracovanie noveho IRP.
			InterlockedIncrement(&PDQ->MStallCount);

			// !!! Ak IRP je prave spracovane, umozni sa nastavenie NOTIFICATION FUNCTION.
			if (PDQ->MCurrentIRP!=NULL)
			{
				// Device busy with this queue.
				++NBusy;
				IBusy=Index;
			}
		}
	}

	// If we didn't finish the loop, we found a queue for which a notification is already pending, which is an error. Unstall any queues that we just stalled in order to backout from this function.
	// !!! Ak NIE VSETKY DEVQUEUES boli STALLED a maju nastavenu NOTIFICATION FUNCTION, vykona sa ROLLBACK cinnosti, ktore FUNCTION vykonala.
	if (Index<NumberOfQueues)
	{
		// Backout from error.
		for (--Index;(int)Index>=0;--Index)
		{
			// !!! Ak NIE VSETKY DEVQUEUES boli STALLED, alebo nie vsetky maju nastavenu NOTIFICATION FUNCTION, vratia sa hodnoty ich STALL COUNTERS do povodnej hodnoty.
			InterlockedDecrement(&Queue[Index]->MStallCount);
		}
		
		// Indicate we have an error.
		Status=STATUS_INVALID_DEVICE_REQUEST;
	}
	// If none of the queues is busy, we can just return STATUS_SUCCESS.
	else if (NBusy==0)
	{
		// Device not busy.
		Status=STATUS_SUCCESS;
	}
	// If just one of the queues is busy, arrange for it call the notification procedure once the current IRP finishes (whereupon somebody will call StartNextPacket on this queue).
	else if (NBusy==1)
	{
		// One queue busy.
		// !!! Ak iba 1 DEVQUEUE ma IRP, ktore je prave spracovane, nastavi sa NOTIFICATION FUNCTION.
		Queue[IBusy]->MNotify=Notify;
		Queue[IBusy]->MNotifyContext=Context;
		Status=STATUS_PENDING;
	}
	// More than one queue is currently busy. We need to arrange for each queue to finish before calling the callback function.
	else
	{
		// Multiple queues busy.
		PNOTIFY_CONTEXT											NewContext=(PNOTIFY_CONTEXT) ExAllocatePoolWithTag(NonPagedPool,sizeof(NOTIFY_CONTEXT),'  CN');

		if (NewContext==NULL)
		{
			// Can't allocate context block.
			for (Index=0;Index<NumberOfQueues;++Index)
			{
				// Unstall the queues we stalled.
				// !!! Ak NIE VSETKY DEVQUEUES boli STALLED, alebo nie vsetky maju nastavenu NOTIFICATION FUNCTION, vratia sa hodnoty ich STALL COUNTERS do povodnej hodnoty.
				InterlockedDecrement(&Queue[Index]->MStallCount);
			}

			Status=STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			// Arrange for notifications.
			NewContext->MContext=NewContext;
			NewContext->MNotify=Notify;
			NewContext->MCount=NBusy;

			for (Index=0;Index<NumberOfQueues;++Index)
			{
				// For each queue.
				PDEVQUEUE										PDQ=Queue[Index];

				if (PDQ->MCurrentIRP==NULL)
				{
					// This queue not busy.
					continue;
				}

				PDQ->MNotify=(PQNOTIFYFUNC) NotificationCallback;
				PDQ->MNotifyContext=(PVOID) NewContext;
			}
			
			Status=STATUS_PENDING;
		}
	}

	// Release all the queue locks. [Note: there used to be a rookie mistake in the following line of code -- "i" is unsigned, so the loop used to wrap it around to FFFFFFFF and led to a crash. Reader and past student Mike Rapp spent many hours isolating this problem.]
	for (Index=(NumberOfQueues-1);int(Index)>=0;--Index)
	{
		// !!! Kedze FUNCTION pracovala s INTERNYM STATE VSETKYCH DEVQUEUES musi uvolnit ich SPIN LOCKS.
		KeReleaseSpinLockFromDpcLevel(&Queue[Index]->MLock);
	}

	KeLowerIrql(OldIRQL);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION skontroluje ci DEVQUEUE je IDLE a ak ano, tak zmeni DEVQUEUE do STATE [STALLED].
GENERICAPI BOOLEAN GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE PDQ)
{
	KIRQL														OldIRQL;

	// !!! Kedze FUNCTION pracuje s INTERNYM STATE DEVQUEUE musi ziskat SPIN LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!! Zisti ci DEVQUEUE prave spracuvava IRP.
	BOOLEAN														Busy=(PDQ->MCurrentIRP!=NULL);

	// !!! Ak DEVQUEUE NESPRACOVAVA IRP, vykona STALLING danej DEVQUEUE.
	if (Busy==FALSE)
	{
		// Ikrementaciou STALL COUNTER sa vykona STALLING danej DEVQUEUE.
		InterlockedIncrement(&PDQ->MStallCount);
	}

	// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	return(Busy);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION skontroluje ci NIEKTORA z DEVQUEUES v DEVQUEUE ARRAY je BUSY. Ak ZIADNA QUEUE NIE JE BUSY, potom STATE VSETKYCH DEVQUEUES v DEVQUEUE ARRAY je zmeneny na STATE [STALLED].
GENERICAPI BOOLEAN GENERIC_EXPORT CheckAnyBusyAndStall(PDEVQUEUE* Queue, ULONG NumberOfQueues, PDEVICE_OBJECT FDO)
{
	// Call CheckBusyAndStall() for each queue. If one of them is busy, back out by unstalling the queues we stalled.
	// !!! Prechadzaju sa VSETKY DEVQUEUES v DEQUEUE ARRAY.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		// !!! Skontroluje sa ci QUEUE je IDLE a ak ANO, potom je DEVQUEUE ATOMICKY zmenena do STATE [STALLED].
		if (CheckBusyAndStall(Queue[Index])!=FALSE)
		{
			// A queue is busy.
			// !!!!! Ak NIEKTORA z DEVQUEUES je BUSY, potom sa vykona 'ROLLBACK' na DEVQUEUES, ktore uz boli [STALLED] a ich STATE je zmeneny SPAT na STATE [READY].
			for (--Index;(int) Index>=0;--Index)
			{
				// !!! Zmeni STATE DEVQUEUES na STATE SPAT na STATE [READY].
				RestartRequests(Queue[Index],FDO);
			}
		
			// Indicate at least one queue is busy.
			return(TRUE);
		}
	}

	// Return FALSE because no queue was busy and all are now stalled.
	return(FALSE);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [STALLED] do STATE [READY], alebo do STATE [STALLED].
// FUNCTION opatovne povoluje spracovanie pozastavenych IRP v DEVQUEUE. IRP, ktore su v DEVQUEUE ulozene su spracovane.
// !!!!! EXTREMNE DOLEZITE je volat FUNCTION pre KAZDU INSTANCIU DEVQUEUE pri spracovani MINOR FUNCTION [IRP_MN_START_DEVICE] v [IRP_MJ_PNP].
GENERICAPI VOID GENERIC_EXPORT RestartRequests(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO)
{
	// The original version of this routine called StartNextPacket() to restart the queue. Reader Sink Ho pointed out a race condition, such that an intervening call to StartPacket() in another thread or on another CPU would cause StartNextPacket() to end up dequeuing a second IRP.
	KIRQL														OldIRQL;

	// !!! Kedze FUNCTION pracuje s INTERNYM STATE DEVQUEUE musi ziskat SPIN LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!! Vykona sa DEKREMENTACIA STALL COUNTER.
	// !!!!! Ak STALL COUNTER je >0, tak DEVQUEUE je STALE STALLED a teda sa NEMOZE spustit vykonavanie IRP.
	if (InterlockedDecrement(&PDQ->MStallCount)>0)
	{
		// Still stalled.
		// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
		KeReleaseSpinLock(&PDQ->MLock,OldIRQL);
		return;
	}
	
	// Dequeue and start the IRP at the head of the list. See the comments in StartNextPacket() for an explanation of the cancel logic.
	// !!!!! Prechadza sa DEVQUEUE a hlada sa PRVE IRP, ktore NIE JE CANCELLED. Zaroven sa zistuje ci nedoslo k ABORT DEVQUEUE (napriklad pri uvolneni DRIVER z PNP MANAGER), alebo ci DEVQUEUE nie je STALLED.
	// !!!!! TENTO CODE je chraneny LOCK PDQ->MLock.
	while (PDQ->MStallCount==0 && PDQ->MCurrentIRP==NULL && PDQ->MAbortStatus==STATUS_SUCCESS && IsListEmpty(&PDQ->MHead)==FALSE)
	{
		// Start first queued IRP.
		PLIST_ENTRY												Next=RemoveHeadList(&PDQ->MHead);
		PIRP													IRPRecord=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		// !!!!! Ak CANCELLATION ROUTINE uz BOLO NASTAVENE na NULL, tak IRP uz JE AKTUALNE SPRACOVAVANE (zacalo byt spracovane pocas vykonavanie FUNCTION), a preto sa hlada DALSIE IRP, ktoreho spracovanie by mohol byt zacate.
		if (IoSetCancelRoutine(IRPRecord,NULL)==NULL)
		{
			// IRP being cancelled right now.
			// Else CancelRoutine shouldn't be NULL !
			ASSERT(IRPRecord->Cancel);
			// !!!!! Specialna FINTA vdaka ktorej sa nasledne volanie RemoveEntryList() v CANCELLATION ROUTINE (ta vola DEVQUEUE FUNCTION CancelRequest()) zabrani NEKOREKTNEMU vymazaniu IRP z IRP QUEUE tak, ze RemoveEntryList() v podstate NIC z IRP QUEUE NESPRAVI.
			InitializeListHead(&IRPRecord->Tail.Overlay.ListEntry);

			// With "start first queued IRP".
			continue;
		}

		// !!! Vybrate IRP sa nastavi ako CURRENT IRP.
		PDQ->MCurrentIRP=IRPRecord;

		// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
		// !!! IRQL sa ponecha na urovni [IRQL=DISPATCH_LEVEL], pretoze CUSTOM ROUTINE StartIO() by sa mala volat pri [IRQL=DISPATCH_LEVEL].
		KeReleaseSpinLockFromDpcLevel(&PDQ->MLock);

		// !!! Zavola sa CUSTOM ROUTINE StartIO(), ktora ma za ulohu vykonat IRP.
		(*PDQ->MStartIO)(FDO,IRPRecord);

		// !!! IRQL sa znizi na povodnu uroven.
		KeLowerIrql(OldIRQL);

		return;
	}

	// No IRPs need to be started (or else all queued IRPs were being cancelled).
	// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [STALLED] do STATE [READY], alebo do STATE [STALLED].
// FUNCTION opatovne povoluje spracovanie pozastavenych IRP v DEVQUEUES z DEVQUEUE ARRAY. IRP, ktore su v jednotlivych DEVQUEUES ulozene su spracovane.
GENERICAPI VOID GENERIC_EXPORT RestartAllRequests(PDEVQUEUE* Queue, ULONG NumberOfQueues, PDEVICE_OBJECT FDO)
{
	// !!! Vykona RESTART kazdej DEVQUEUE.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		RestartRequests(Queue[Index],FDO);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION caka na skoncenie aktualne spracovavaneho IRP.
// !!!!! FUNCTION je volana pri spracovanie IRP s MINOR FUNCTION [IRP_MN_STOP_DEVICE].
GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIRP(PDEVQUEUE PDQ)
{
	// First reset the event that StartNextPacket sets each time.
	// !!! Vykona sa RESET EVENT na SIGNALIZACIU ktoreho FUNCTION bude cakat.
	KeClearEvent(&PDQ->MEventStop);

	// Under protection of our spin lock, check to see if there's a current IRP. Since whoever called us should also have stalled requests, no-one can sneak in after we release the spin lock and start a new request behind our back.
	// Should be stalled now !
	ASSERT(PDQ->MStallCount!=0);
	
	KIRQL														OldIRQL;

	// !!! Kedze FUNCTION pracuje s INTERNYM STATE DEVQUEUE musi ziskat SPIN LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	// !!! Zisti sa ci IRP je v DEVQUEUE prave SPRACOVAVANE a teda ci je vobec NUTNE vykonat WAIT.
	BOOLEAN														MustWait=(PDQ->MCurrentIRP!=NULL);

	// !!! Kedze FUNCTION pracovala s INTERNYM STATE DEVQUEUE musi uvolnit SPIN LOCK.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	if (MustWait!=FALSE)
	{
		// !!!!! Ak je WAITING na ukoncenie pracovania IRP NUTNY, vykona sa pomocou FUNCTION KeWaitForSingleObject().
		// !!!!! EVENT sa uvolnuje pri UKONCENI IRP vo FUNCTION StartNextPacket().
		KeWaitForSingleObject(&PDQ->MEventStop,Executive,KernelMode,FALSE,NULL);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION caka na skoncenie aktualne spracovavaneho IRP vo VSETKYCH DEVQUEUES v DEVQUEUE ARRAY.
// !!!!! FUNCTION je volana pri spracovanie IRP s MINOR FUNCTION [IRP_MN_STOP_DEVICE].
GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIRPS(PDEVQUEUE* Queue, ULONG NumberOfQueues)
{
	// !!! Pocka kym VSETKY DEVQUEUES NEUKONCIA spracovanie aktualne spracovavanych IRP.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		WaitForCurrentIRP(Queue[Index]);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [READY], alebo zo STATE [STALLED] do STATE [REJECTING].
// !!!!! FUNCTION ODSTRANI VSETKY IRP zo DEVQUEUE volanim FUNCTION IoCompleteRequest() s ERROR CODE a zaroven zabrani dalsiemu spracovaniu IRP v DEVQUEUE. Vsetky IRP, ktore po zavolani tejto FUNCTION pridu do DEVQUEUE budu UKONCENE s ERROR VALUE.
GENERICAPI VOID GENERIC_EXPORT AbortRequests(PDEVQUEUE PDQ, NTSTATUS Status)
{
	// !!! Nastavuje DEVQUEUE STATE na STATE [REJECTING], ktore sposobi, ze VSETKY IRP, ktore budu odoslane do DEVQUEUE budu OKAMZITE UKONCENE volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
	PDQ->MAbortStatus=Status;

	// !!!!! FUNCTION OKAMZITE ukonci VSETKY IRP, ktore su ulozene v DEVQUEUE volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
	// !!! Kedze 2. PARAMETER je nastaveny na NULL, odstrania sa VSETKY IRP v DEVQUEUE.
	CleanupRequests(PDQ,NULL,Status);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION ODSTRANI VSETKY IRP zo vsetkych DEVQUEUES volanim FUNCTION IoCompleteRequest() s ERROR CODE a zaroven zabrani dalsiemu spracovaniu IRP vo VSETKYCH DEVQUEUES v DEVQUEUE ARRAY. Vsetky IRP, ktore po zavolani tejto FUNCTION pridu do DEVQUEUES budu UKONCENE s ERROR VALUE.
GENERICAPI VOID GENERIC_EXPORT AbortAllRequests(PDEVQUEUE* Queue, ULONG NumberOfQueues, NTSTATUS Status)
{
	// !!! Vykona ABORT VSETKYCH DEVQUEUES.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		AbortRequests(Queue[Index],Status);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vracia informaciu o tom ci DEVQUEUE je v STATE [REJECTING] a teda ci vsetky IRP, ktore do DEVQUEUE pridu budu UKONCENE s ERROR VALUE.
GENERICAPI NTSTATUS GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE PDQ)
{
	return(PDQ->MAbortStatus);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [REJECTING] do STATE [READY], alebo do STATE [STALLED].
// FUNCTION opatovne povoluje spracovanie IRP v DEVQUEUE. Neguje tym volanie FUNCTION AbortRequests().
GENERICAPI VOID GENERIC_EXPORT AllowRequests(PDEVQUEUE PDQ)
{
	// !!! Odblokuje ABORTED DEVQUEUE.
	PDQ->MAbortStatus=STATUS_SUCCESS;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava prechod zo STATE [REJECTING] do STATE [READY], alebo do STATE [STALLED].
// FUNCTION opatovne povoluje spracovanie IRP vo VSETKYCH DEVQUEUES z DEVQUEUE ARRAYS. Neguje tym volanie FUNCTION AbortAllRequests().
GENERICAPI VOID GENERIC_EXPORT AllowAllRequests(PDEVQUEUE* Queue, ULONG NumberOfQueues)
{
	// !!! Odblokuje vsetky ABORTED DEVQUEUES.
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		AllowRequests(Queue[Index]);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION robi CLEANUP vsetkych IRP vytvorenych zadanym FILE_OBJECT. Je volana z DISPATCH FUNCTION [IRP_MJ_CLEANUP], ale takisto pri vykonani ABORT pre danu DEVQUEUE.
GENERICAPI VOID GENERIC_EXPORT CleanupRequests(PDEVQUEUE PDQ, PFILE_OBJECT FOP, NTSTATUS Status)
{
	LIST_ENTRY													CancelList;

	// !!! Inicializuje sa CANCEL LIST do ktoreho sa ulozia IRP, ktore boli vytvorene FILE_OBJECT_FOP.
	InitializeListHead(&CancelList);

	// Create a list of IRPs that belong to the same file object.
	KIRQL														OldIRQL;

	// !!! Kedze sa ide pracovat s DEVQUEUE, je NUTNE ziskat LOCK.
	KeAcquireSpinLock(&PDQ->MLock,&OldIRQL);

	PLIST_ENTRY													First=&PDQ->MHead;
	PLIST_ENTRY													Next;

	// !!! Prechadza sa DEVQUEUE.
	for (Next=First->Flink;Next!=First;)
	{
		// For each queued IRP.
		PIRP													IRPRecord=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		// !!! Pre dany IRP sa ziska IO_STACK_LOCATION.
		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(IRPRecord);

		// Follow the chain to the next IRP now (so that the next iteration of the loop is properly setup whether we dequeue this IRP or not).
		PLIST_ENTRY												Current=Next;

		Next=Next->Flink;

		// !!!!! Porovna sa FILE_OBJECT IRP s hladanym FILE_OBJECT.
		// Skip this IRP if it's not for the same file object as the current IRP_MJ_CLEANUP.
		if (FOP!=NULL && Stack->FileObject!=FOP)
		{
			// Not for same file object.
			continue;
		}

		// !!!!! Ak je CANCELLATION ROUTINE na NULL, tak sa PRAVE v TEJTO CHVILI niekto pokusa vykona IRP CANCELLATION (volanim FUNCTION IoCancelIrp()) a tento IRP sa ponecha, aby bol CANCELLED.
		// (After Hanrahan) Set the CancelRoutine pointer to NULL. If it was already NULL, someone is trying to cancel this IRP right now, so just leave it on the queue and let them do it as soon as we release the spin lock.
		if (IoSetCancelRoutine(IRPRecord,NULL)==NULL)
		{
			continue;
		}

		// !!! Najdene IRP sa ODSTRANI z DEVQUEUE.
		RemoveEntryList(Current);

		// !!! Najdene IRP sa ZARADI z CANCEL QUEUE.
		InsertTailList(&CancelList,Current);
	}

	// !!! DEVQUEUE LOCK sa uvolni.
	// Release the spin lock. We're about to undertake a potentially time-consuming operation that might conceivably result in a deadlock if we keep the lock.
	KeReleaseSpinLock(&PDQ->MLock,OldIRQL);

	// !!! Vykona sa IRP CANCELLATION pre IRP vytvorene zadanym FILE_OBJECT.
	// Complete the selected requests.
	while(IsListEmpty(&CancelList)==FALSE)
	{
		// !!! IRP sa odstrani z CANCEL LIST.
		// Cancel selected requests.
		Next=RemoveHeadList(&CancelList);

		PIRP													IRPRecord=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		IRPRecord->IoStatus.Status=Status;

		// !!! IRP sa ukonci zo zadanym NTSTATUS.
		IoCompleteRequest(IRPRecord,IO_NO_INCREMENT);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION robi CLEANUP vsetkych IRP vytvorenych zadanym FILE_OBJECT pre VSETKY DEVQUEUE v DEVQUEUE ARRYA. Je volana z DISPATCH FUNCTION [IRP_MJ_CLEANUP].
GENERICAPI VOID GENERIC_EXPORT CleanupAllRequests(PDEVQUEUE* Queue, ULONG NumberOfQueues, PFILE_OBJECT FOP, NTSTATUS Status)
{
	for (ULONG Index=0;Index<NumberOfQueues;++Index)
	{
		CleanupRequests(Queue[Index],FOP,Status);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION inicializuje DEVQUEUE.
GENERICAPI VOID GENERIC_EXPORT InitializeQueue(PDEVQUEUE PDQ, PDRIVER_STARTIO StartIO)
{
	// !!! DEVQUEUE pouziva NON-THREAD SAFE QUEUE. Je to preto, lebo CODE pracujuci s DEVQUEUE bude VZDY bezat v LOCK.
	InitializeListHead(&PDQ->MHead);

	// !!! LOCK, ktory chrani pristup k DEVQUEUE. Pouziva sa aj pri zabezpeceni LOCKING pri IRP CANCELLATION.
	KeInitializeSpinLock(&PDQ->MLock);

	// !!! KAZDA DEVQUEUE ma VLASTNU StartIo() FUNCTION, ktora je zavolana, ked ma nastat zaciatok spracovania IRP.
	// !!! Ulohou StartIo() je ODSTARTOVAT spracovanie IRP. To znaci, ze ulohou IRP je INCIALIZOVAT DEVICE, aby zacalo spracovavat IRP.
	PDQ->MStartIO=StartIO;

	// !!!!! CODE musi nastavit MStallCount na 1. No na to, aby CODE uz fungoval tak MUSI v IRP s MINOR FUNCTION [IRP_MN_START_DEVICE] zavolat FUNCTION RestartRequests(), ktora tuto hodnotu zhodi na 0.
	PDQ->MStallCount=1;

	// !!! MEMBER MCurrentIRP obsahuje IRP, ktore sa prave vykonava. VACSINA DRIVERS vykonava naraz IBA 1 IRP a 1 DEVQUEUE moze vykonavat NARAZ IBA 1 IRP.
	PDQ->MCurrentIRP=NULL;

	// !!! EVENT sa nastavuje pri UKONCENI IRP vo FUNCTION StartNextPacket(), ktora sa vola VZDY pri ukonceni IRP.
	KeInitializeEvent(&PDQ->MEventStop,NotificationEvent,FALSE);

	PDQ->MAbortStatus=(NTSTATUS) 0;
	PDQ->MNotify=NULL;
	PDQ->MNotifyContext=0;
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION vyvolava CALLBACK FUNCTION.
VOID NotificationCallback(PNOTIFY_CONTEXT Context)
{
	if (InterlockedDecrement(&Context->MCount)>0)
	{
		return;
	}

	(*Context->MNotify)(Context->MContext);

	ExFreePool(Context);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION vracia aktualne spracovavane IRP.
GENERICAPI PIRP GENERIC_EXPORT GetCurrentIRP(PDEVQUEUE PDQ)
{
	return(PDQ->MCurrentIRP);
}
//-------------------------------------------------------------------------------------------------------