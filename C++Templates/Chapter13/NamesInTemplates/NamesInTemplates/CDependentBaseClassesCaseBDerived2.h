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
class CDependentBaseClassesCaseBDerived2 final : public CDependentBaseClassesCaseBBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! Do CLASS SCOPE sa vlozi FIELD z BASE CLASS.
		using													CDependentBaseClassesCaseBBase<TType>::MBaseField;

	public:
		void Test(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseBDerived2<TType>::Test(void)
{
	// !!!!! NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS je NAJDENY, pretoze bol vlozeny do DERIVED CLASS SCOPE pomocou USING.
	MBaseField=300;

	// !!!!! NON-DEPENDENT NAME [MBaseField] definovany v BASE CLASS je NAJDENY, pretoze bol vlozeny do DERIVED CLASS SCOPE pomocou USING.
	std::wcout << L"CASE B - DERIVED 2 - TEST - TYPE [" << GetTypeInfoName<TType>() << L"] BASE FIELD [" << MBaseField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------