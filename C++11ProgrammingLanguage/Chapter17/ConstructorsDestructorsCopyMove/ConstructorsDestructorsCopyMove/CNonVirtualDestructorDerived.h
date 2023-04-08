//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CNonVirtualDestructorBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CNonVirtualDestructorDerived final : public CNonVirtualDestructorBase
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		virtual int GetValue(void) const noexcept override
		{
			return(MValue);
		}

	public:
		CNonVirtualDestructorDerived(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualDestructorDerived CALLED !" << std::endl;
		}

		~CNonVirtualDestructorDerived(void)
		{
			std::wcout << L"DESTRUCTOR ~CNonVirtualDestructorDerived CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------