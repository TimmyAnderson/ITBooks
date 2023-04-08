//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "MyDebug.h"
//-----------------------------------------------------------------------------
// !!! STRUCTURE ak ma byt pouziva v CLASS [atomic<T>] MUSI byt TRIVIALLY COPYABLE. To znaci, ze NESMIE mat CUSTOM COPY OPERATIONS a MUSI mat DEFAULT CONSTRUCTOR.
struct SSmallStructure1
{
//-----------------------------------------------------------------------------
	public:
		int														MField;

	public:
		int GetField(void) const noexcept
		{
			return(MField);
		}

	public:
		SSmallStructure1(void)
			: MField(0)
		{
		}

		SSmallStructure1(int Field)
			: MField(Field)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------