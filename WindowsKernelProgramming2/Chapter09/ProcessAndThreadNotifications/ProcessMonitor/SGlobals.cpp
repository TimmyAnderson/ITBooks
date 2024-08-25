//----------------------------------------------------------------------------------------------------------------------
#include "SGlobals.h"
#include "SFullItem.h"
#include "SItemHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SGlobals::SGlobals(ULONG MaxCount)
	: MItemsHead(), MCount(0), MMaxCount(MaxCount), MLock()
{
	InitializeListHead(&MItemsHead);
}
//----------------------------------------------------------------------------------------------------------------------
SGlobals::~SGlobals(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SGlobals::AddItem(LIST_ENTRY* Entry)
{
	CLocker<CFastMutex>											Locker(MLock);
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
	CLocker<CFastMutex>											Locker(MLock);
	{
		InsertHeadList(&MItemsHead,Entry);

		MCount++;
	}
}
//----------------------------------------------------------------------------------------------------------------------
LIST_ENTRY* SGlobals::RemoveItem(void)
{
	CLocker<CFastMutex>											Locker(MLock);
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