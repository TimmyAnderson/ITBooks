//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceBase1 : virtual public CVirtualInheritanceSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CVirtualInheritanceBase1(const std::wstring& Value)
			: CVirtualInheritanceSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceBase1 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceBase1(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceBase1 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------