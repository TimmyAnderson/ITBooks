//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CMethodHidingBase
{
//-----------------------------------------------------------------------------
	public:
		void Method1(int) const
		{
			std::wcout << L"METHOD CMethodHidingBase::Method1(INT) CALLED !" << std::endl;
		}

		void Method2(int,int) const
		{
			std::wcout << L"METHOD CMethodHidingBase::Method2(INT,INT) CALLED !" << std::endl;
		}

	public:
		CMethodHidingBase(void)
		{
		}

		virtual ~CMethodHidingBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------