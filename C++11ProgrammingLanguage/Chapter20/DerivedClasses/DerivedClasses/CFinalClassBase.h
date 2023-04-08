//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CFinalClassBase final
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(void) const
		{
			std::wcout << L"METHOD CFinalClassBase::VirtualMethod1() CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(void) const
		{
			std::wcout << L"METHOD CFinalClassBase::VirtualMethod2() CALLED !" << std::endl;
		}

	public:
		CFinalClassBase(void)
		{
		}

		virtual ~CFinalClassBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------