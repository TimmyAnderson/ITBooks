//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CFinalMethodBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(void) const
		{
			std::wcout << L"METHOD CFinalMethodBase::VirtualMethod1() CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(void) const
		{
			std::wcout << L"METHOD CFinalMethodBase::VirtualMethod2() CALLED !" << std::endl;
		}

	public:
		CFinalMethodBase(void)
		{
		}

		virtual ~CFinalMethodBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------