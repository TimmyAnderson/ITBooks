//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDeletedOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		// !!! ZABRANI sa ziskaniu POINTER na OBJECT.
		CDeletedOperators* operator&(void)=delete;

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CDeletedOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------