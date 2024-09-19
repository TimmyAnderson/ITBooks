//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CInterlockedGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CInterlocked;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CInterlocked<LONG64> : public CInterlockedGlobal<LONG64>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using CMemoryOperators::operator new;
		using CMemoryOperators::operator delete;

	public:
		using CInterlockedGlobal<LONG64>::GetValue;
		using CInterlockedGlobal<LONG64>::SetValue;

	public:
		using CInterlockedGlobal<LONG64>::Exchange;
		using CInterlockedGlobal<LONG64>::CompareExchange;

	public:
		using CInterlockedGlobal<LONG64>::And;
		using CInterlockedGlobal<LONG64>::Or;
		using CInterlockedGlobal<LONG64>::Xor;

	public:
		using CInterlockedGlobal<LONG64>::BitTestAndSetBit;
		using CInterlockedGlobal<LONG64>::BitTestAndResetBit;

	public:
		using CInterlockedGlobal<LONG64>::Increment;
		using CInterlockedGlobal<LONG64>::Decrement;

	public:
		CInterlocked(void);
		CInterlocked(LONG64 Variable);
		~CInterlocked(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------