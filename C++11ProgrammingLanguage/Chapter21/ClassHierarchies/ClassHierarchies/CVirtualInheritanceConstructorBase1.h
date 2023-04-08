//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceConstructorSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceConstructorBase1 : virtual public CVirtualInheritanceConstructorSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CVirtualInheritanceConstructorBase1(const std::wstring& Value)
			// !!!!! Ak je CLASS 'CVirtualInheritanceConstructorBase1' pouzita ako BASE CLASS voci CLASS 'CVirtualInheritanceConstructorDerived', tak sa CONSTRUCTOR 'CVirtualInheritanceConstructorSuperBase' TU NEZAVOLA, pretoze ho vola CONSTRUCTOR CLASS 'CVirtualInheritanceDerived'.
			: CVirtualInheritanceConstructorSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceConstructorBase1 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceConstructorBase1(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceConstructorBase1 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------