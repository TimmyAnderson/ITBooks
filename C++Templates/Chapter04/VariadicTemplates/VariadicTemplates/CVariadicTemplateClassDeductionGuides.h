//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale NIE DEFINITION VARIADIC TEMPLATE CLASS.
template<typename... TTypes>
class CVariadicTemplateClassDeductionGuides;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
class CVariadicTemplateClassDeductionGuides<TThis,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Obsahuje 1. TEMPLATE PARAMETER.
		TThis													MField;
		// !!! Obsahuje CLASS 'CVariadicTemplateClassDeductionGuides<>', ktora uklada <2,N> TEMPLATE PARAMETER.
		CVariadicTemplateClassDeductionGuides<TTypes...>						MOtherFields;

	public:
		void Print(void) const;

	public:
		CVariadicTemplateClassDeductionGuides(TThis This, TTypes... Others);
		virtual ~CVariadicTemplateClassDeductionGuides(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClassDeductionGuides<TThis,TTypes...>::CVariadicTemplateClassDeductionGuides(TThis This, TTypes... Others)
	: MField(This), MOtherFields(Others...)
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<TThis,TTypes...> - CONSTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClassDeductionGuides<TThis,TTypes...>::~CVariadicTemplateClassDeductionGuides(void) noexcept
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<TThis,TTypes...> - DESTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
void CVariadicTemplateClassDeductionGuides<TThis,TTypes...>::Print(void) const
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<TThis,TTypes...> - TYPE [" << GetTypeInfoName<TThis>() << L"] !" << std::endl;

	// !!! Vypise sa 1. FIELD.
	std::wcout << L"CVariadicTemplateClassDeductionGuides<TThis,TTypes...> - VALUE [" << MField << L"] !" << std::endl;

	// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych FIELDS.
	MOtherFields.Print();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre koniec RECURSION.
template<>
class CVariadicTemplateClassDeductionGuides<> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;

	public:
		CVariadicTemplateClassDeductionGuides(void);
		virtual ~CVariadicTemplateClassDeductionGuides(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! CONSTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClassDeductionGuides<>].
CVariadicTemplateClassDeductionGuides<>::CVariadicTemplateClassDeductionGuides(void)
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<> - CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DESTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! DESTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClassDeductionGuides<>].
CVariadicTemplateClassDeductionGuides<>::~CVariadicTemplateClassDeductionGuides(void) noexcept
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<> - DESTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre koniec RECURSION.
// !!!!! METHOD je definovana pre TEMPLATE SPECIALIZATION [CVariadicTemplateClassDeductionGuides<>].
void CVariadicTemplateClassDeductionGuides<>::Print(void) const
{
	std::wcout << L"CVariadicTemplateClassDeductionGuides<> - END of PRINT METHOD !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DEDUCTION GUIDE, ktory mapuje PARAMETETERS tu definovaneho PSEUDO CONSTRUCTOR na TEMPLATE ARGUMENTS TEMPLATE CLASS.
// !!!!! DEDUCTION GUIDE pre PARAMETER TYPE 'const wchar_t*' pouzije TYPE [wstring] a pre ostatne TYPES povodne TYPES.
template <typename... TTypes>
CVariadicTemplateClassDeductionGuides(TTypes... Values) -> CVariadicTemplateClassDeductionGuides<std::conditional_t<std::is_same_v<TTypes,const wchar_t*>,std::wstring,TTypes>...>;
//----------------------------------------------------------------------------------------------------------------------