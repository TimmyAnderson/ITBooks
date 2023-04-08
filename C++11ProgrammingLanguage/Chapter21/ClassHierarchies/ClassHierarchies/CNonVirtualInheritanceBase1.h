//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CNonVirtualInheritanceSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CNonVirtualInheritanceBase1 : public CNonVirtualInheritanceSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CNonVirtualInheritanceBase1(const std::wstring& Value)
			: CNonVirtualInheritanceSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualInheritanceBase1 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CNonVirtualInheritanceBase1(void) override
		{
			std::wcout << L"DESTRUCTOR CNonVirtualInheritanceBase1 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------