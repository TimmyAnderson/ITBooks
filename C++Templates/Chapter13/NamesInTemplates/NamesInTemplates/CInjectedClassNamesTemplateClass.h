//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename TTemplate>
class CInjectedClassNamesTemplateClassInner final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void PrintType(const CString& Text) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename TTemplate>
void CInjectedClassNamesTemplateClassInner<TTemplate>::PrintType(const CString& Text) const
{
	std::wcout << Text << L" - TEMPLATE CLASS TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CInjectedClassNamesTemplateClass final
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TLocalType>
	friend class CInjectedClassNamesTemplateClass;

	private:
		void PrintType(const CString& Text) const;
	
	public:
		void PrintInjectedClassNames(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CInjectedClassNamesTemplateClass<TType>::PrintType(const CString& Text) const
{
	std::wcout << Text << L" - TEMPLATE CLASS TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CInjectedClassNamesTemplateClass<TType>::PrintInjectedClassNames(void) const
{
	{
		// !!! Vdaka CLASS NAME INJECTION sa CODE [CInjectedClassNamesTemplateClass] interpretuje ako CODE [CInjectedClassNamesTemplateClass<TType>].
		CInjectedClassNamesTemplateClass						Object;

		Object.PrintType(L"OBJECT 1");
	}

	PrintLineSeparator();

	{
		// !!! Vdaka CLASS NAME INJECTION sa CODE [CInjectedClassNamesTemplateClass<int>] interpretuje ako CODE [CInjectedClassNamesTemplateClass<int>].
		CInjectedClassNamesTemplateClass<int>					Object;

		Object.PrintType(L"OBJECT 2");
	}

	PrintLineSeparator();

	{
		// !!! Vdaka CLASS NAME INJECTION sa CODE [CInjectedClassNamesTemplateClassInner<CInjectedClassNamesTemplateClass>] interpretuje ako CODE [CInjectedClassNamesTemplateClassInner<CInjectedClassNamesTemplateClass>].
		CInjectedClassNamesTemplateClassInner<CInjectedClassNamesTemplateClass>	Object;

		Object.PrintType(L"INNER OBJECT 3");
	}

	PrintLineSeparator();

	{
		// !!! Pre CLASS [CInjectedClassNamesTemplateClass] sa pouziva SCOPE RESOLUTION OPERATOR [::], takze sa jedna o QUALIFIED NAME.
		CInjectedClassNamesTemplateClassInner<::CInjectedClassNamesTemplateClass>	Object;

		Object.PrintType(L"INNER OBJECT 4");
	}
}
//----------------------------------------------------------------------------------------------------------------------