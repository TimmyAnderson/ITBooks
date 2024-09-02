//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DON"T have CONSTRUCTOR and DESTURCTOR. Can be USED as a GLOBAL VARIABLE.
class CFastMutexGlobal : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	protected:
		FAST_MUTEX												MMutex;

	public:
		void Init(void);

	public:
		void Lock(void);
		void Unlock(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------