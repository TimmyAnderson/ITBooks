//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
class CInjectedClassNamesVariadicTemplateClass final
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TLocalType, typename... TTLocalypes>
	friend class CInjectedClassNamesVariadicTemplateClass;

	private:
		void PrintType(const CString& Text) const;
	
	public:
		void PrintInjectedClassNames(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void CInjectedClassNamesVariadicTemplateClass<TType,TTypes...>::PrintType(const CString& Text) const
{
	std::wcout << Text << " - VARIADIC TEMPLATE CLASS TYPE [" << GetTypeInfoName<decltype(*this)>() << "]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void CInjectedClassNamesVariadicTemplateClass<TType,TTypes...>::PrintInjectedClassNames(void) const
{
	{
		// !!! Vdaka CLASS NAME INJECTION sa CODE [CInjectedClassNamesVariadicTemplateClass] interpretuje ako CODE [CInjectedClassNamesVariadicTemplateClass<TType,TTypes...>].
		CInjectedClassNamesVariadicTemplateClass				Object;

		Object.PrintType(L"OBJECT 1");
	}

	PrintLineSeparator();

	{
		// !!! Vdaka CLASS NAME INJECTION sa CODE [CInjectedClassNamesVariadicTemplateClass<CString,CString,int,double>] interpretuje ako CODE [CInjectedClassNamesVariadicTemplateClass<CString,CString,int,double>].
		CInjectedClassNamesVariadicTemplateClass<CString,CString,int,double>	Object;

		Object.PrintType(L"OBJECT 2");
	}
}
//----------------------------------------------------------------------------------------------------------------------