//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CTypeidVirtualBase.h"
//-----------------------------------------------------------------------------
class CTypeidVirtualDerived : public CTypeidVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const override
		{
			std::wcout << L"METHOD CTypeidVirtualDerived::VirtualMethod() CALLED !";
		}

	public:
		CTypeidVirtualDerived(void)
		{
		}

		virtual ~CTypeidVirtualDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------