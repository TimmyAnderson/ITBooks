//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CFinalMethodDerived.h"
//-----------------------------------------------------------------------------
class CFinalMethodSuperDerived : public CFinalMethodDerived
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(void) const override
		{
			std::wcout << L"METHOD CFinalMethodSuperDerived::VirtualMethod1() CALLED !" << std::endl;
		}

		/*
		// !!! METHOD VirtualMethod2() NEMOZE BYT OVERRIDDEN, pretoze bola v CLASS 'CFinalMethodDerived' oznacena ako FINAL.
		virtual void VirtualMethod2(void) const override final
		{
			std::wcout << L"METHOD CFinalMethodSuperDerived::VirtualMethod2() CALLED !" << std::endl;
		}
		*/

	public:
		CFinalMethodSuperDerived(void)
		{
		}

		virtual ~CFinalMethodSuperDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------