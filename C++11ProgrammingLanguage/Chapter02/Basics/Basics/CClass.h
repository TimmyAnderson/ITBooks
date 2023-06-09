//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CClass
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
		CClass(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CClass CALLED !" << std::endl;
		}

		~CClass(void)
		{
			std::wcout << L"DESTRUCTOR CClass CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------