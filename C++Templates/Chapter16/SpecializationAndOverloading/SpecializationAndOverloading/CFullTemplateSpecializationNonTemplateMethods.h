//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFullTemplateSpecializationNonTemplateMethods final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		void Print1(void) const;
		void Print2(void) const;
		void Print3(TType Parameter) const;

	public:
		CFullTemplateSpecializationNonTemplateMethods(TType Field);
		virtual ~CFullTemplateSpecializationNonTemplateMethods(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFullTemplateSpecializationNonTemplateMethods<TType>::CFullTemplateSpecializationNonTemplateMethods(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFullTemplateSpecializationNonTemplateMethods<TType>::~CFullTemplateSpecializationNonTemplateMethods(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CFullTemplateSpecializationNonTemplateMethods<TType>::Print1(void) const
{
	std::wcout << L"PRIMARY TEMPLATE METHOD 1 - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CFullTemplateSpecializationNonTemplateMethods<TType>::Print2(void) const
{
	std::wcout << L"PRIMARY TEMPLATE METHOD 2 - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CFullTemplateSpecializationNonTemplateMethods<TType>::Print3(TType Parameter) const
{
	std::wcout << L"PRIMARY TEMPLATE METHOD 3 - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION NON-TEMPLATE METHOD SPECIALIZATION.
template<>
void CFullTemplateSpecializationNonTemplateMethods<double>::Print2(void) const;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION NON-TEMPLATE METHOD SPECIALIZATION.
template<>
void CFullTemplateSpecializationNonTemplateMethods<double>::Print3(double Parameter) const;
//----------------------------------------------------------------------------------------------------------------------