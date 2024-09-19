//----------------------------------------------------------------------------------------------------------------------
#include "TestSequencedSinglyLinkedLists.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "SSequencedSinglyListItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SequencedSinglyLinkedListsData final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		const ULONG												MNumberOfItems;
		const bool												MDump;

	public:
		volatile LONG64											MExitThread;
		SLIST_HEADER											MHead;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public:
		SequencedSinglyLinkedListsData(ULONG NumberOfItems, bool Dump)
			: MNumberOfItems(NumberOfItems), MDump(Dump), MExitThread(0), MHead()
		{
			InitializeSListHead(&MHead);
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SequencedSinglyLinkedListsThread1(PVOID StartContext)
{
	constexpr USHORT											MAX_NUMBER_OF_ITEMS=50000;

	SequencedSinglyLinkedListsData*								Data=static_cast<SequencedSinglyLinkedListsData*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	ULONG														NumberOfAddedItems=0;

	for(ULONG Index=0;Index<Data->MNumberOfItems;Index++)
	{
		USHORT													NumberOfItemsInList=ExQueryDepthSList(&Data->MHead);

		if (NumberOfItemsInList==MAX_NUMBER_OF_ITEMS)
		{
			//KdPrint(("!!!!!!!!!! ROUTINE [%s] - LIST is FULL.\n",FunctionName));
			--Index;
			continue;
		}

		SSequencedSinglyListItem*								Item=static_cast<SSequencedSinglyListItem*>(ExAllocatePool2(POOL_FLAG_PAGED,sizeof(SSequencedSinglyListItem),MY_TAG));

		if (Item!=nullptr)
		{
			Item->MValue=(Index+1);

			ExpInterlockedPushEntrySList(&Data->MHead,&Item->MEntry);

			if (Data->MDump==true)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - ADDED ITEM [%lu].\n",FunctionName,Item->MValue));
			}

			++NumberOfAddedItems;
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 is OUT of MEMORY.\n",FunctionName));
			break;
		}
	}

	// !!! Nastavi sa FLAG, ze THREAD ukoncil.
	InterlockedExchange64(&Data->MExitThread,1);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - RESULT - ADDED ITEMS [%lu].\n",FunctionName,NumberOfAddedItems));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void SequencedSinglyLinkedListsThread2(PVOID StartContext)
{
	SequencedSinglyLinkedListsData*								Data=static_cast<SequencedSinglyLinkedListsData*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(1000);

	ULONG														NumberOfDeletedItems=0;

	while(true)
	{
		// !!!!! Nacita sa SHARED VARIABLE obsahujuca informaciu ci THREAD 1 skoncil.
		// !!!!! Toto citanie sa MUSI vykonat PRED WHILE cyklom vyberajucim ITEMS z LIST. Dovodom je, ze ak by sa toto volanie spravilo po WHILE cykle, mohlo by sa stat nasledujuce.
		// !!!!! 1. THREAD 2 by ukoncil WHILE kedze LIST je EMPTY.
		// !!!!! 2. Este skor nez by THREAD 2 nacital SHARED VARIABLE by sa THREAD 2 pozastavil.
		// !!!!! 3. THREAD 1 by pridal nove ITEMS do LIST a nastavil SHARED VARIABLE.
		// !!!!! 4. Ak by sa teraz rozbehol THREAD 2 a nacital SHARED VARIABLE, tak ten by bol nastaveny a THREAD 2 by sa ukoncil. To by vsak sposobilo, ze niektore ITEMS by este NEBOLI ODSTRANENE z LIST a doslo by k MEMORY LEAK.
		LONG64													ExitThread=InterlockedOr64(&Data->MExitThread,0);
		
		while(true)
		{
			PSLIST_ENTRY										Entry=ExpInterlockedPopEntrySList(&Data->MHead);

			if (Entry!=nullptr)
			{
				SSequencedSinglyListItem*						Item=CONTAINING_RECORD(Entry,SSequencedSinglyListItem,MEntry);

				if (Data->MDump==true)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - DELETED ITEM [%lu].\n",FunctionName,Item->MValue));
				}

				ExFreePoolWithTag(Item,MY_TAG);

				++NumberOfDeletedItems;
			}
			else
			{
				break;
			}
		}

		if (ExitThread!=0)
		{
			break;
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - RESULT - DELETED ITEMS [%lu].\n",FunctionName,NumberOfDeletedItems));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSequencedSinglyLinkedLists(DEVICE_OBJECT* DeviceObject, IRP* Irp, ULONG NumberOfItems, bool Dump)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		SequencedSinglyLinkedListsData							Data(NumberOfItems,Dump);

		PETHREAD												ThreadObject1=nullptr;
		PETHREAD												ThreadObject2=nullptr;

		do
		{
			Status=CHelpers::CreateThread(DeviceObject,"111",SequencedSinglyLinkedListsThread1,&Data,&ThreadObject1);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
				break;
			}

			Status=CHelpers::CreateThread(DeviceObject,"222",SequencedSinglyLinkedListsThread2,&Data,&ThreadObject2);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
				break;
			}

			PVOID												Object[]{ThreadObject1,ThreadObject2};
			constexpr ULONG										Count=(sizeof(Object)/sizeof(Object[0]));
			PLARGE_INTEGER										Timeout=nullptr;
			KWAIT_BLOCK											WaitBlockArray[Count];

			// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
			Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,WaitBlockArray);

			if (Status==STATUS_SUCCESS)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREADS FINISHED.\n",FunctionName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREADS with ERROR CODE [%lX].\n",FunctionName,Status));
			}
		}
		while(false);

		if (ThreadObject2!=nullptr)
		{
			ObDereferenceObject(ThreadObject2);
			ThreadObject2=nullptr;
		}

		if (ThreadObject1!=nullptr)
		{
			ObDereferenceObject(ThreadObject1);
			ThreadObject1=nullptr;
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------