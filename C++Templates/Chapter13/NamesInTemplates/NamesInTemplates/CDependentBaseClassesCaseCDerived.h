//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CDependentBaseClassesCaseCBase.h"
#include "MyDebug.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDependentBaseClassesCaseCDerived final : public CDependentBaseClassesCaseCBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(CDependentBaseClassesCaseCBase<TType>::EEnum Value=CDependentBaseClassesCaseCBase<TType>::VALUE_1);
		virtual void VirtualMethod2(const CDependentBaseClassesCaseCBase<TType>::EEnum& Value);

	public:
		void Test(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseCDerived<TType>::VirtualMethod1(CDependentBaseClassesCaseCBase<TType>::EEnum Value)
{
	std::wcout << L"CASE C - DERIVED - VIRTUAL METHOD 1 - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseCDerived<TType>::VirtualMethod2(const CDependentBaseClassesCaseCBase<TType>::EEnum& Value)
{
	std::wcout << L"CASE C - DERIVED - VIRTUAL METHOD 2 - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CDependentBaseClassesCaseCDerived<TType>::Test(void)
{
	typename CDependentBaseClassesCaseCDerived<TType>::EEnum	Value=CDependentBaseClassesCaseCDerived<TType>::VALUE_2;

	std::wcout << L"CASE C - TEST - VALUE [" << Value << L"]." << std::endl;

	this->VirtualMethod1();

	VirtualMethod2(Value);
}
//----------------------------------------------------------------------------------------------------------------------