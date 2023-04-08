//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "COperatorHiding1.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
COperatorHiding1 operator+(const COperatorHiding1& Left, const COperatorHiding1& Right)
{
	std::wcout << "NON-MEMBER OPERATOR+ CALLED !" << std::endl;

	return(COperatorHiding1(Left.GetValue()+Right.GetValue()));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class COperatorHiding2 final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		COperatorHiding2 operator+(const COperatorHiding1& Value)
		{
			std::wcout << "MEMBER OPERATOR+ CALLED !" << std::endl;

			// !!! Kedze C++ NEROBI OPERATOR HIDING, tak je mozne volat OPERATOR FUNCTION.
			int													IntValue=(Value+Value).GetValue();

			std::wcout << "INT VALUE [" << IntValue << L"] !" << std::endl;

			return(COperatorHiding2(MValue+Value.GetValue()));
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		COperatorHiding2(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------