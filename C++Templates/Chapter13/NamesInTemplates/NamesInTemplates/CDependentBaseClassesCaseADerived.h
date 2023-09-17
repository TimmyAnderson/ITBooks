//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CDependentBaseClassesCaseABase.h"
#include "MyDebug.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDependentBaseClassesCaseADerived final : public CDependentBaseClassesCaseABase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Test(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseADerived<TType>::Test(void)
{
	// !!!!! Bez pouzitia KEYWORD [this] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	this->MBaseField=100;

	// !!!!! Bez pouzitia KEYWORD [this] sa NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS NENAJDE, pretoze C++ NEVYHLADAVA NON-DEPENDENT NAMES v DEPENDENT BASE CLASSES.
	std::wcout << L"CASE A - DERIVED - TYPE [" << GetTypeInfoName<TType>() << L"] BASE FIELD [" << this->MBaseField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------