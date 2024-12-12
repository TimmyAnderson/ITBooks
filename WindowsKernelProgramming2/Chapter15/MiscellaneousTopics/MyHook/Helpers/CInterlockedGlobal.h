//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DON'T have CONSTRUCTOR and DESTURCTOR. Can be USED as a GLOBAL VARIABLE.
template<typename TType>
class CInterlockedGlobal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CInterlockedGlobal<LONG64> : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		volatile LONG64											MVariable;

	public:
		LONG64 GetValue(void);
		void SetValue(LONG64 Value);

	public:
		LONG64 Exchange(LONG64 Value);
		LONG64 CompareExchange(LONG64 Value, LONG64 Comperand);

	public:
		LONG64 And(LONG64 Value);
		LONG64 Or(LONG64 Value);
		LONG64 Xor(LONG64 Value);

	public:
		LONG64 BitTestAndSetBit(LONG64 Offset);
		LONG64 BitTestAndResetBit(LONG64 Offset);

	public:
		LONG64 Increment(void);
		LONG64 Decrement(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------