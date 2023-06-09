//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CField3 final
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
		CField3(void)
			: MValue()
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CField3 CALLED !" << std::endl;
		}

		CField3(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CField3 CALLED ! VALUE [" << Value << L"] !" << std::endl;
		}

		virtual ~CField3(void)
		{
			std::wcout << L"DESTRUCTOR ~CField3 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------