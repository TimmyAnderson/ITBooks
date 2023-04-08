//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMemberInitializerListBase1
{
//-----------------------------------------------------------------------------
	private:
		int														MValueBase1;

	public:
		int GetValueBase1(void) const noexcept
		{
			return(MValueBase1);
		}

	public:
		CMemberInitializerListBase1(int ValueBase1)
			: MValueBase1(ValueBase1)
		{
			std::wcout << L"CONSTRUCTOR CMemberInitializerListBase1 CALLED !" << std::endl;
		}

		virtual ~CMemberInitializerListBase1(void)
		{
			std::wcout << L"DESTRUCTOR ~CMemberInitializerListBase1 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------