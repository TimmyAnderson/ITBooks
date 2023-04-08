//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceConstructorBase1.h"
#include "CVirtualInheritanceConstructorBase2.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva sa VIRTUAL INHERITANCE.
class CVirtualInheritanceConstructorDerived : public CVirtualInheritanceConstructorBase1, public CVirtualInheritanceConstructorBase2
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Kedze sa pouzila VIRTUAL INHERITANCE, instancia CLASS 'CVirtualInheritanceSuperBase' sa nachadza v CLASS HIERARCHY IBA RAZ a preto je treba EXPLICITNE INICIALIZOVAT.
		CVirtualInheritanceConstructorDerived(const std::wstring& Value1, const std::wstring& Value2, const std::wstring& Value3)
			: CVirtualInheritanceConstructorSuperBase(Value1), CVirtualInheritanceConstructorBase1(Value2), CVirtualInheritanceConstructorBase2(Value3)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceConstructorDerived - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceConstructorDerived(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceConstructorDerived CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------