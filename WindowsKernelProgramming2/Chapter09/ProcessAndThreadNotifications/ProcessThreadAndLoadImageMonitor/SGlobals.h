//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "Helpers/CFastMutex.h"
#include "Helpers/CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SGlobals final : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		LIST_ENTRY												MItemsHead;
		ULONG													MCount;
		ULONG													MMaxCount;
		CFastMutex												MLock;

	public:
		void AddItem(LIST_ENTRY* Entry);
		void AddHeadItem(LIST_ENTRY* Entry);
		LIST_ENTRY* RemoveItem(void);

	public:
		SGlobals(ULONG MaxCount);
		~SGlobals(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------