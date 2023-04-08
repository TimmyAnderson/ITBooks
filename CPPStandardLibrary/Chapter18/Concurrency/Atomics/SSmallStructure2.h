//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "MyDebug.h"
//-----------------------------------------------------------------------------
// !!! STRUCTURE ak ma byt pouziva v CLASS [atomic<T>] MUSI byt TRIVIALLY COPYABLE. To znaci, ze NESMIE mat CUSTOM COPY OPERATIONS a MUSI mat DEFAULT CONSTRUCTOR.
struct SSmallStructure2
{
//-----------------------------------------------------------------------------
	public:
		int														MField1;
		int														MField2;

	public:
		int GetField1(void) const noexcept
		{
			return(MField1);
		}

		int GetField2(void) const noexcept
		{
			return(MField2);
		}

	public:
		SSmallStructure2(void)
			: MField1(0), MField2(0)
		{
		}

		SSmallStructure2(int Field1, int Field2)
			: MField1(Field1), MField2(Field2)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------