//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class COverrideBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const
		{
			std::wcout << L"METHOD COverrideBase::VirtualMethod() CALLED !" << std::endl;
		}

		void NonVirtualMethod(void) const
		{
			std::wcout << L"METHOD COverrideBase::NonVirtualMethod() CALLED !" << std::endl;
		}

		/*
		// !!! C++ umoznuje aplikovat KEYWORD [override] IBA na OVERRIDEN METHODS. Kedze vsak METHOD VirtualMethodBase() NIE JE OVERRIDDEN, kedze CLASS 'COverrideBase' NEMA BASE CLASS, COMPILER hodi ERROR.
		virtual void VirtualMethodBase(void) const override
		{
			std::wcout << L"METHOD COverrideBase::VirtualMethodBase() CALLED !" << std::endl;
		}
		*/

	public:
		COverrideBase(void)
		{
		}

		virtual ~COverrideBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------