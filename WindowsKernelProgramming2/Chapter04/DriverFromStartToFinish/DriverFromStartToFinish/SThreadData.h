//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! Tento HEADER FILE je SHARED medzi USER MODE CODE a KERNEL MODE CODE.
struct SThreadData
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													ThreadID;
		int														Priority;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------