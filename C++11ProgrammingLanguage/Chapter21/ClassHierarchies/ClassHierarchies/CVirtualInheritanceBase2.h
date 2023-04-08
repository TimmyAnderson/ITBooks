//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceBase2 : virtual public CVirtualInheritanceSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CVirtualInheritanceBase2(const std::wstring& Value)
			: CVirtualInheritanceSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceBase2 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceBase2(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceBase2 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------