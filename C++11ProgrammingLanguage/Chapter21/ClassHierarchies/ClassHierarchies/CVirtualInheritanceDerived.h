//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualInheritanceBase1.h"
#include "CVirtualInheritanceBase2.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva sa VIRTUAL INHERITANCE.
class CVirtualInheritanceDerived : public CVirtualInheritanceBase1, public CVirtualInheritanceBase2
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Kedze sa pouzila VIRTUAL INHERITANCE, instancia CLASS 'CVirtualInheritanceSuperBase' sa nachadza v CLASS HIERARCHY IBA RAZ a preto je treba EXPLICITNE INICIALIZOVAT.
		CVirtualInheritanceDerived(const std::wstring& Value1, const std::wstring& Value2, const std::wstring& Value3)
			: CVirtualInheritanceSuperBase(Value1), CVirtualInheritanceBase1(Value2), CVirtualInheritanceBase2(Value3)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceDerived - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceDerived(void) override
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceDerived CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------