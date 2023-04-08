//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "MyDebug.h"
//-----------------------------------------------------------------------------
// !!! STRUCTURE ak ma byt pouziva v CLASS [atomic<T>] MUSI byt TRIVIALLY COPYABLE. To znaci, ze NESMIE mat CUSTOM COPY OPERATIONS a MUSI mat DEFAULT CONSTRUCTOR.
struct SBigStructure
{
//-----------------------------------------------------------------------------
	public:
		int														MField1;
		int														MField2;
		int														MField3;

	public:
		int GetField1(void) const noexcept
		{
			return(MField1);
		}

		int GetField2(void) const noexcept
		{
			return(MField2);
		}

		int GetField3(void) const noexcept
		{
			return(MField3);
		}

	public:
		SBigStructure(void)
			: MField1(0), MField2(0), MField3(0)
		{
		}

		SBigStructure(int Field1, int Field2, int Field3)
			: MField1(Field1), MField2(Field2), MField3(Field3)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------