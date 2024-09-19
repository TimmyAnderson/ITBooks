#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "SMyTreeKey.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class SMyTreeItem final : public SMyTreeKey
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		ULONG													MValue;

	public:
		ULONG GetValue(void) const noexcept;

	public:
		SMyTreeItem(ULONG Key, ULONG Value);
		~SMyTreeItem(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------