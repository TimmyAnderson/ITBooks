//----------------------------------------------------------------------------------------------------------------------
#include "TestsListOperations.h"
#include <wdm.h>
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SMyListItem
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		wchar_t													MValue1[100];

		// !!! Umoznuje vytvorit LIST.
		LIST_ENTRY												MLink;

		ULONG													MValue2;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SMyListItem* AllocateMyListItem(const wchar_t* Value1, ULONG Value2)
{
	constexpr SIZE_T											LIST_ITEM_SIZE=sizeof(SMyListItem);

	SMyListItem*												ListItem=(SMyListItem*)ExAllocatePool2(POOL_FLAG_PAGED,LIST_ITEM_SIZE,MY_TAG);

	if (ListItem!=nullptr)
	{
		wcscpy_s(ListItem->MValue1,Value1);
		ListItem->MValue2=Value2;
	}
	
	return(ListItem);
}
//----------------------------------------------------------------------------------------------------------------------
void FreeMyListItem(SMyListItem* ListItem)
{
	ExFreePoolWithTag(ListItem,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
void FreeMyList(PLIST_ENTRY ListHeadEntry)
{
	PLIST_ENTRY													ListItemEntry=ListHeadEntry->Flink;

	while(ListItemEntry!=ListHeadEntry)
	{
		PLIST_ENTRY												ListItemEntryToDelete=ListItemEntry;

		ListItemEntry=ListItemEntry->Flink;

		SMyListItem*											ListItemToDelete=CONTAINING_RECORD(ListItemEntryToDelete,SMyListItem,SMyListItem::MLink);

		FreeMyListItem(ListItemToDelete);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintMyListForward(const char* FunctionName, PLIST_ENTRY ListHeadEntry)
{
	BOOLEAN														IsEmpty=IsListEmpty(ListHeadEntry);
	SMyListItem*												ListHead=CONTAINING_RECORD(ListHeadEntry,SMyListItem,SMyListItem::MLink);

	KdPrint(("!!!!! FUNCTION [%s] - FORWARD - IS EMPTY [%hhu] - LIST HEAD [%S,%lu] !!!\n",FunctionName,IsEmpty,ListHead->MValue1,ListHead->MValue2));

	for(PLIST_ENTRY ListItemEntry=ListHeadEntry->Flink;ListItemEntry!=ListHeadEntry;ListItemEntry=ListItemEntry->Flink)
	{
		SMyListItem*											ListItem=CONTAINING_RECORD(ListItemEntry,SMyListItem,SMyListItem::MLink);

		KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void PrintMyListBackward(const char* FunctionName, PLIST_ENTRY ListHeadEntry)
{
	BOOLEAN														IsEmpty=IsListEmpty(ListHeadEntry);
	SMyListItem*												ListHead=CONTAINING_RECORD(ListHeadEntry,SMyListItem,SMyListItem::MLink);

	KdPrint(("!!!!! FUNCTION [%s] - BACKWARD - IS EMPTY [%hhu] - LIST HEAD [%S,%lu] !!!\n",FunctionName,IsEmpty,ListHead->MValue1,ListHead->MValue2));

	for(PLIST_ENTRY ListItemEntry=ListHeadEntry->Blink;ListItemEntry!=ListHeadEntry;ListItemEntry=ListItemEntry->Blink)
	{
		SMyListItem*											ListItem=CONTAINING_RECORD(ListItemEntry,SMyListItem,SMyListItem::MLink);

		KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsListOperations(void)
{
	const char*													FunctionName=__FUNCTION__;

	SMyListItem													ListHead;

	wcscpy_s(ListHead.MValue1,L"HEAD");
	ListHead.MValue2=0;

	PLIST_ENTRY													ListHeadEntry=&ListHead.MLink;

	// !!! Inicializuje LIST HEAD.
	// !!! Vznikne LIST [HEAD].
	InitializeListHead(ListHeadEntry);

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		SMyListItem*											ListItem=AllocateMyListItem(L"AAA",111);

		if (ListItem!=nullptr)
		{
			PLIST_ENTRY											ListItemEntry=&ListItem->MLink;

			// !!! Vznikne LIST [HEAD---AAA].
			InsertHeadList(ListHeadEntry,ListItemEntry);

			KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] ADDED to HEAD !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
		}
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		SMyListItem*											ListItem=AllocateMyListItem(L"BBB",222);

		if (ListItem!=nullptr)
		{
			PLIST_ENTRY											ListItemEntry=&ListItem->MLink;

			// !!! Vznikne LIST [HEAD---BBB---AAA].
			InsertHeadList(ListHeadEntry,ListItemEntry);

			KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] ADDED to HEAD !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
		}
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		SMyListItem*											ListItem=AllocateMyListItem(L"CCC",333);

		if (ListItem!=nullptr)
		{
			PLIST_ENTRY											ListItemEntry=&ListItem->MLink;

			// !!! Vznikne LIST [HEAD---CCC---BBB---AAA].
			InsertHeadList(ListHeadEntry,ListItemEntry);

			KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] ADDED to HEAD !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
		}
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		SMyListItem*											ListItem=AllocateMyListItem(L"DDD",444);

		if (ListItem!=nullptr)
		{
			PLIST_ENTRY											ListItemEntry=&ListItem->MLink;

			// !!! Vznikne LIST [HEAD---CCC---BBB---AAA---DDD].
			InsertTailList(ListHeadEntry,ListItemEntry);

			KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] ADDED to TAIL !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
		}
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		SMyListItem*											ListItem=AllocateMyListItem(L"EEE",555);

		if (ListItem!=nullptr)
		{
			PLIST_ENTRY											ListItemEntry=&ListItem->MLink;

			// !!! Vznikne LIST [HEAD---CCC---BBB---AAA---DDD---EEE].
			InsertTailList(ListHeadEntry,ListItemEntry);

			KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] ADDED to TAIL !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));
		}
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		PLIST_ENTRY												ListItemEntryToDelete=ListHeadEntry->Flink->Flink->Flink;
		SMyListItem*											ListItem=CONTAINING_RECORD(ListItemEntryToDelete,SMyListItem,SMyListItem::MLink);

		// !!! Vznikne LIST [HEAD---CCC---BBB---DDD---EEE].
		RemoveEntryList(ListItemEntryToDelete);

		KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] REMOVED from MIDDLE !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));

		FreeMyListItem(ListItem);
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		// !!! Vznikne LIST [HEAD---BBB---DDD---EEE].
		PLIST_ENTRY												ListItemEntryDeleted=RemoveHeadList(ListHeadEntry);
		SMyListItem*											ListItem=CONTAINING_RECORD(ListItemEntryDeleted,SMyListItem,SMyListItem::MLink);

		KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] REMOVED from HEAD !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));

		FreeMyListItem(ListItem);
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	{
		// !!! Vznikne LIST [HEAD---BBB---DDD].
		PLIST_ENTRY												ListItemEntryDeleted=RemoveTailList(ListHeadEntry);
		SMyListItem*											ListItem=CONTAINING_RECORD(ListItemEntryDeleted,SMyListItem,SMyListItem::MLink);

		KdPrint(("!!!!! FUNCTION [%s] LIST ITEM [%S,%lu] REMOVED from TAIL !!!\n",FunctionName,ListItem->MValue1,ListItem->MValue2));

		FreeMyListItem(ListItem);
	}

	PrintMyListForward(FunctionName,ListHeadEntry);
	PrintMyListBackward(FunctionName,ListHeadEntry);

	FreeMyList(ListHeadEntry);
}
//----------------------------------------------------------------------------------------------------------------------