//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "COverrideBase.h"
//-----------------------------------------------------------------------------
class COverrideDerived : public COverrideBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const override
		{
			std::wcout << L"METHOD COverrideDerived::VirtualMethod() CALLED !" << std::endl;
		}

		/*
		// !!! C++ umoznuje aplikovat KEYWORD [override] IBA na OVERRIDEN METHODS. Kedze vsak METHOD NonVirtualMethod() NIE JE v BASE CLASS 'COverrideBase' deklarovana ako VIRTUAL, nedojde k METHOD OVERRIDDEN a COMPILER hodi ERROR.
		virtual void NonVirtualMethod(void) const override
		{
			std::wcout << L"METHOD COverrideDerived::NonVirtualMethod() CALLED !" << std::endl;
		}
		*/

	public:
		COverrideDerived(void)
		{
		}

		virtual ~COverrideDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------