//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CAmbiguities1Y final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CAmbiguities1Y(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------