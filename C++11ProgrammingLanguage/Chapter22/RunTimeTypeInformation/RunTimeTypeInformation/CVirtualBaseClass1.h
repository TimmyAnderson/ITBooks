//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
// !!! CLASS MA VIRTUAL METHOD.
class CVirtualBaseClass1
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod(void) const
		{
			std::wcout << L"METHOD CVirtualBaseClass1::VirtualMethod() CALLED !" << std::endl;
		}

	public:
		CVirtualBaseClass1(void)
		{
		}

		virtual ~CVirtualBaseClass1(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------