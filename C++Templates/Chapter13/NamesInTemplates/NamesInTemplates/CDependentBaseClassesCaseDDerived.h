//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CDependentBaseClassesCaseDBaseNonDependent.h"
#include "CDependentBaseClassesCaseDBaseDependent.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDependentBaseClassesCaseDDerived final : public CDependentBaseClassesCaseDBaseNonDependent, public CDependentBaseClassesCaseDBaseDependent<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Test(typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_NON_DEPENDENT Parameter1, typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_DEPENDENT* Parameter2) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseDDerived<TType>::Test(typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_NON_DEPENDENT Parameter1, typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_DEPENDENT* Parameter2) const
{
	// !!! TYPE sa referuje na CURRENT INSTANTIATION.
	typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_NON_DEPENDENT	Value1=Parameter1;

	// !!! TYPE sa referuje na UNKNOWN SPECIALIZATION.
	typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_DEPENDENT*	Value2=Parameter2;

	std::wcout << L"CASE D - DERIVED - TEST - TYPE [" << GetTypeInfoName<typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_NON_DEPENDENT>() << L"] VALUE 1 [" << Value1 << L"]." << std::endl;

	std::wcout << L"CASE D - DERIVED - TEST - TYPE [" << GetTypeInfoName<typename CDependentBaseClassesCaseDDerived<TType>::TYPE_BASE_DEPENDENT>() << L"] VALUE 2 [" << (*Value2) << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------