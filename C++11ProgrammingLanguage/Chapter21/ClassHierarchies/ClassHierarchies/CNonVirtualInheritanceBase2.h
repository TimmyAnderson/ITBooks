//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CNonVirtualInheritanceSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CNonVirtualInheritanceBase2 : public CNonVirtualInheritanceSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CNonVirtualInheritanceBase2(const std::wstring& Value)
			: CNonVirtualInheritanceSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualInheritanceBase2 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CNonVirtualInheritanceBase2(void) override
		{
			std::wcout << L"DESTRUCTOR CNonVirtualInheritanceBase2 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------