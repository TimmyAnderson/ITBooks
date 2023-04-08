//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CFinalMethodBase.h"
//-----------------------------------------------------------------------------
class CFinalMethodDerived : public CFinalMethodBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(void) const override
		{
			std::wcout << L"METHOD CFinalMethodDerived::VirtualMethod1() CALLED !" << std::endl;
		}

		// !!! METHOD je deklarovana ako FINAL METHOD, ktora NEMOZE byt viac OVERRIDEN.
		virtual void VirtualMethod2(void) const override final
		{
			std::wcout << L"METHOD CFinalMethodDerived::VirtualMethod2() CALLED !" << std::endl;
		}

	public:
		CFinalMethodDerived(void)
		{
		}

		virtual ~CFinalMethodDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------