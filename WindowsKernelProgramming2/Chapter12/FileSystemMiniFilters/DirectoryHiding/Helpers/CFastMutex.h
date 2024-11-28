//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CFastMutexGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFastMutex final : private CFastMutexGlobal
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using CMemoryOperators::operator new;
		using CMemoryOperators::operator delete;

	public:
		using CFastMutexGlobal::Lock;
		using CFastMutexGlobal::Unlock;

	public:
		CFastMutex(void);
		~CFastMutex(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------