//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CFunctionCallOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int operator()(int Value1, int Value2)
		{
			std::wcout << "MEMBER OPERATOR() CALLED !" << std::endl;

			return(MValue+Value1+Value2);
		}

	public:
		CFunctionCallOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------