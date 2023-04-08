//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMemberInitializerListBase2
{
//-----------------------------------------------------------------------------
	private:
		int														MValueBase2;

	public:
		int GetValueBase2(void) const noexcept
		{
			return(MValueBase2);
		}

	public:
		CMemberInitializerListBase2(int ValueBase2)
			: MValueBase2(ValueBase2)
		{
			std::wcout << L"CONSTRUCTOR CMemberInitializerListBase2 CALLED !" << std::endl;
		}

		virtual ~CMemberInitializerListBase2(void)
		{
			std::wcout << L"DESTRUCTOR ~CMemberInitializerListBase2 CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------