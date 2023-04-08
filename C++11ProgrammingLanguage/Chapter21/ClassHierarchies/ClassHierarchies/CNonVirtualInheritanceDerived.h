//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CNonVirtualInheritanceBase1.h"
#include "CNonVirtualInheritanceBase2.h"
//-------------------------------------------------------------------------------------------------------
class CNonVirtualInheritanceDerived : public CNonVirtualInheritanceBase1, public CNonVirtualInheritanceBase2
{
//-------------------------------------------------------------------------------------------------------
	public:
		CNonVirtualInheritanceDerived(const std::wstring& Value1, const std::wstring& Value2)
			: CNonVirtualInheritanceBase1(Value1), CNonVirtualInheritanceBase2(Value2)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualInheritanceDerive - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] CALLED !" << std::endl;
		}

		virtual ~CNonVirtualInheritanceDerived(void) override
		{
			std::wcout << L"DESTRUCTOR CNonVirtualInheritanceDerived CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------