//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CPureVirtualBase.h"
//-----------------------------------------------------------------------------
class CPureVirtualDerived : public CPureVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void PureVirtualMethod(void) const override
		{
			std::wcout << L"METHOD CPureVirtualDerived::PureVirtualMethod() CALLED !" << std::endl;

			// !!! Pretoze METHOD CPureVirtualBase::PureVirtualMethod() NIE JE definovana, LINKER hodi ERROR. ERROR nehadze COMPILER, ale az LINKER s tym, ze METHOD nevie najst.
			//CPureVirtualBase::PureVirtualMethod();
		}

		virtual void PureVirtualMethodWithDefinition(void) const override
		{
			std::wcout << L"METHOD CPureVirtualDerived::PureVirtualMethodWithDefinition() CALLED !" << std::endl;

			// !!! Vola sa PURE VIRTUAL METHOD z BASE CLASS.
			CPureVirtualBase::PureVirtualMethodWithDefinition();
		}

	public:
		CPureVirtualDerived(void)
		{
		}

		virtual ~CPureVirtualDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------