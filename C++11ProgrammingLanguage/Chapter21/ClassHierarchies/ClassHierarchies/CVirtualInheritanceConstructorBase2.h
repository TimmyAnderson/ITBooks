//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceConstructorSuperBase.h"
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceConstructorBase2 : virtual public CVirtualInheritanceConstructorSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		CVirtualInheritanceConstructorBase2(const std::wstring& Value)
			// !!!!! Ak je CLASS 'CVirtualInheritanceConstructorBase2' pouzita ako BASE CLASS voci CLASS 'CVirtualInheritanceConstructorDerived', tak sa CONSTRUCTOR 'CVirtualInheritanceConstructorSuperBase' TU NEZAVOLA, pretoze ho vola CONSTRUCTOR CLASS 'CVirtualInheritanceDerived'.
			: CVirtualInheritanceConstructorSuperBase(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceConstructorBase2 - VALUE [" << Value << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceConstructorBase2(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceConstructorBase2 CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------