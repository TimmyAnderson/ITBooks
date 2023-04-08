//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
// !!! CLASS NEMA VIRTUAL METHODS.
class CNonVirtualBaseClass
{
//-----------------------------------------------------------------------------
	public:
		void NonVirtualMethod(void) const
		{
			std::wcout << L"METHOD CNonVirtualBaseClass::VirtualMethod() CALLED !" << std::endl;
		}

	public:
		CNonVirtualBaseClass(void)
		{
		}

		~CNonVirtualBaseClass(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------