//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CBaseClassOperators
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CBaseClassOperators operator+(const CBaseClassOperators& Value)
		{
			std::wcout << "MEMBER CBaseClassOperators::OPERATOR+ CALLED !" << std::endl;

			return(MValue+Value.GetValue());
		}

		virtual CBaseClassOperators operator-(const CBaseClassOperators& Value)
		{
			std::wcout << "MEMBER CBaseClassOperators::OPERATOR- CALLED !" << std::endl;

			return(MValue-Value.GetValue());
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CBaseClassOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------