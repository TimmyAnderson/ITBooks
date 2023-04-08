//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CTypeidNonVirtualBase.h"
//-----------------------------------------------------------------------------
class CTypeidNonVirtualDerived : public CTypeidNonVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		void MethodInDerivedClass(void) const
		{
			std::wcout << L"METHOD CTypeidNonVirtualDerived::MethodInDerivedClass() CALLED !";
		}

	public:
		CTypeidNonVirtualDerived(void)
		{
		}

		~CTypeidNonVirtualDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------