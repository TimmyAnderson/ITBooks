//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CDependentBaseClassesCaseBBase.h"
#include "MyDebug.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDependentBaseClassesCaseBDerived1 final : public CDependentBaseClassesCaseBBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Test1(void);
		void Test2(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseBDerived1<TType>::Test1(void)
{
	// !!!!! Bez pouzitia KEYWORD [this] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	this->MBaseField=100;

	// !!!!! Bez pouzitia KEYWORD [this] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	std::wcout << L"CASE B - DERIVED 1 - TEST 1 - TYPE [" << GetTypeInfoName<TType>() << L"] BASE FIELD [" << this->MBaseField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseBDerived1<TType>::Test2(void)
{
	// !!!!! Bez pouzitia CODE [CDependentBaseClassesCaseBBase<TType>] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	CDependentBaseClassesCaseBBase<TType>::MBaseField=200;

	// !!!!! Bez pouzitia CODE [CDependentBaseClassesCaseBBase<TType>] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	std::wcout << L"CASE B - DERIVED 1 - TEST 2 - TYPE [" << GetTypeInfoName<TType>() << L"] BASE FIELD [" << CDependentBaseClassesCaseBBase<TType>::MBaseField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------