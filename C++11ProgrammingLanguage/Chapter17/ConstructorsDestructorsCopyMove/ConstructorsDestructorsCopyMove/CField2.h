//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CField2 final
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
		CField2(void)
			: MValue()
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CField2 CALLED !" << std::endl;
		}

		CField2(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CField2 CALLED ! VALUE [" << Value << L"] !" << std::endl;
		}

		virtual ~CField2(void)
		{
			std::wcout << L"DESTRUCTOR ~CField2 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------