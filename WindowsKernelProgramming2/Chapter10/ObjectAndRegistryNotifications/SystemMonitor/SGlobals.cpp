//----------------------------------------------------------------------------------------------------------------------
#include "SGlobals.h"
#include "SFullItem.h"
#include "SItemHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SGlobals::AddItem(LIST_ENTRY* Entry)
{
	CLocker<CFastMutexGlobal>									Locker(MLock);
	{
		if (MCount==MMaxCount)
		{
			PLIST_ENTRY											Head=RemoveHeadList(&MItemsHead);
			SFullItem<SItemHeader>*								FullItem=CONTAINING_RECORD(Head,SFullItem<SItemHeader>,MEntry);

			ExFreePoolWithTag(FullItem,MY_TAG);

			KdPrint(("PROCESS INFO REMOVED FROM LIST - LIST is FULL.\n"));

			MCount--;
		}

		InsertTailList(&MItemsHead,Entry);

		MCount++;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void SGlobals::AddHeadItem(LIST_ENTRY* Entry)
{
	CLocker<CFastMutexGlobal>									Locker(MLock);
	{
		InsertHeadList(&MItemsHead,Entry);

		MCount++;
	}
}
//----------------------------------------------------------------------------------------------------------------------
LIST_ENTRY* SGlobals::RemoveItem(void)
{
	CLocker<CFastMutexGlobal>									Locker(MLock);
	{
		PLIST_ENTRY												Item=RemoveHeadList(&MItemsHead);

		if (Item==&MItemsHead)
		{
			return(nullptr);
		}
		else
		{
			MCount--;

			return(Item);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SGlobals::Init(ULONG MaxCount)
{
	InitializeListHead(&MItemsHead);
	MCount=0;
	MMaxCount=MaxCount;
	MLock.Init();
}
//----------------------------------------------------------------------------------------------------------------------