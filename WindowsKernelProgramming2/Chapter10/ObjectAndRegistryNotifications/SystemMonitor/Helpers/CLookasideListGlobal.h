//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DON"T have CONSTRUCTOR and DESTURCTOR. Can be USED as a GLOBAL VARIABLE.
template<typename TType>
class CLookasideListGlobal final : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		LOOKASIDE_LIST_EX										MLookaside;

	public:
		NTSTATUS Init(POOL_TYPE Pool, ULONG Tag);
		void Delete(void);

	public:
		TType* Alloc(void);
		void Free(TType* Pointer);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
NTSTATUS CLookasideListGlobal<TType>::Init(POOL_TYPE Pool, ULONG Tag)
{
	NTSTATUS													Status=ExInitializeLookasideListEx(&MLookaside,nullptr,nullptr,Pool,0,sizeof(TType),Tag,0);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CLookasideListGlobal<TType>::Delete(void)
{
	ExDeleteLookasideListEx(&MLookaside);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType* CLookasideListGlobal<TType>::Alloc(void)
{
	TType*														Buffer=(TType*)ExAllocateFromLookasideListEx(&MLookaside);

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CLookasideListGlobal<TType>::Free(TType* Pointer)
{
	ExFreeToLookasideListEx(&MLookaside,Pointer);
}
//----------------------------------------------------------------------------------------------------------------------