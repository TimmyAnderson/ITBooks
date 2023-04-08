//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CMethodHidingBase.h"
//-----------------------------------------------------------------------------
class CMethodHidingDerived : public CMethodHidingBase
{
//-----------------------------------------------------------------------------
	public:
		void Method1(double) const
		{
			std::wcout << L"METHOD CMethodHidingDerived::Method1(DOUBLE) CALLED !" << std::endl;
		}

		void Method2(double) const
		{
			std::wcout << L"METHOD CMethodHidingDerived::Method2(DOUBLE) CALLED !" << std::endl;
		}

	public:
		CMethodHidingDerived(void)
		{
		}

		virtual ~CMethodHidingDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------