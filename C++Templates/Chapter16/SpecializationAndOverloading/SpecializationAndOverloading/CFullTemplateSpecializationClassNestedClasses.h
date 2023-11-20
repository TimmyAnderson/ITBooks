//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OUTER PRIMARY TEMPLATE CLASS.
template<typename TOuterType>
class CFullTemplateSpecializationClassNestedClassesOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! INNER PRIMARY TEMPLATE CLASS.
		template<typename TInnerType>
		class CFullTemplateSpecializationClassNestedClassesInner final
		{
//----------------------------------------------------------------------------------------------------------------------
			public:
				void Print(TInnerType Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TOuterType>
template<typename TInnerType>
void CFullTemplateSpecializationClassNestedClassesOuter<TOuterType>::CFullTemplateSpecializationClassNestedClassesInner<TInnerType>::Print(TInnerType Parameter) const
{
	std::wcout << L"PRIMARY INNER TEMPLATE CLASS METHOD - OUTER TYPE [" << GetTypeInfoName<TOuterType>() << L"] INNER TYPE [" << GetTypeInfoName<TInnerType>() << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OUTER TEMPLATE CLASS SPECIALIZATION.
template<>
class CFullTemplateSpecializationClassNestedClassesOuter<long> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! INNER TEMPLATE CLASS SPECIALIZATION.
		template<typename TInnerType>
		class CFullTemplateSpecializationClassNestedClassesInner final
		{
//----------------------------------------------------------------------------------------------------------------------
			public:
				void Print(TInnerType Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! INNER TEMPLATE CLASS SPECIALIZATION.
// !!!!! COMPILER hodi ERROR. C++ NEUMOZNUJE, aby po SYNTAXI [template<TEMPLATE_PARAMETERS>] nasledovala SYNTAX [template<>].
template<typename TOuterType>
template<>
class CFullTemplateSpecializationClassNestedClassesOuter<TOuterType>::CFullTemplateSpecializationClassNestedClassesInner<double> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri OUTER CLASS SPECIALIZATION sa NESMIE pouzit SYNTAX [template<>].
template<typename TInnerType>
void CFullTemplateSpecializationClassNestedClassesOuter<long>::CFullTemplateSpecializationClassNestedClassesInner<TInnerType>::Print(TInnerType Parameter) const
{
	std::wcout << L"OUTER TEMPLATE CLASS SPECIALIZATION <long> INNER TEMPLATE CLASS METHOD - OUTER TYPE [" << GetTypeInfoName<long>() << L"] INNER TYPE [" << GetTypeInfoName<TInnerType>() << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! INNER TEMPLATE CLASS SPECIALIZATION pre OUTER TEMPLATE CLASS SPECIALIZATION.
template<>
template<typename TInnerType>
class CFullTemplateSpecializationClassNestedClassesOuter<wchar_t>::CFullTemplateSpecializationClassNestedClassesInner
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(TInnerType Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri INNER CLASS SPECIALIZATION je NUTNE pouzit SYNTAX [template<>].
template<>
template<typename TInnerType>
void CFullTemplateSpecializationClassNestedClassesOuter<wchar_t>::CFullTemplateSpecializationClassNestedClassesInner<TInnerType>::Print(TInnerType Parameter) const
{
	std::wcout << L"OUTER TEMPLATE CLASS SPECIALIZATION <wchar_t> INNER TEMPLATE CLASS METHOD - OUTER TYPE [" << GetTypeInfoName<wchar_t>() << L"] INNER TYPE [" << GetTypeInfoName<TInnerType>() << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! INNER TEMPLATE CLASS SPECIALIZATION pre OUTER TEMPLATE CLASS SPECIALIZATION.
template<>
template<>
class CFullTemplateSpecializationClassNestedClassesOuter<bool>::CFullTemplateSpecializationClassNestedClassesInner<double>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(double Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pretoze OUTER TEMPLATE CLASS [CFullTemplateSpecializationClassNestedClassesOuter<long>] je DEFINED VYSSIE v CODE, pouziva sa iba RAZ SYNTAX [template<>].
template<>
class CFullTemplateSpecializationClassNestedClassesOuter<long>::CFullTemplateSpecializationClassNestedClassesInner<short>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(short Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------