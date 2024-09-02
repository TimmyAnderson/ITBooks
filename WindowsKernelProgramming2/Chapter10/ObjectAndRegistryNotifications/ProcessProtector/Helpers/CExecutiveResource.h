//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CExecutiveResourceGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CExecutiveResource final : private CExecutiveResourceGlobal
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using CMemoryOperators::operator new;
		using CMemoryOperators::operator delete;

	public:
		using CExecutiveResourceGlobal::Lock;
		using CExecutiveResourceGlobal::Unlock;

		using CExecutiveResourceGlobal::LockShared;
		using CExecutiveResourceGlobal::UnlockShared;

		using CExecutiveResourceGlobal::GetSharedWaiterCount;
		using CExecutiveResourceGlobal::GetExclusiveWaiterCount;

	public:
		CExecutiveResource(void);
		~CExecutiveResource(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------