//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale NIE DEFINITION VARIADIC TEMPLATE CLASS.
template<typename... TTypes>
class CVariadicTemplateClass1;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
class CVariadicTemplateClass1<TThis,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Obsahuje 1. TEMPLATE PARAMETER.
		TThis													MField;
		// !!! Obsahuje CLASS 'CVariadicTemplateClass1<>', ktora uklada <2,N> TEMPLATE PARAMETER.
		CVariadicTemplateClass1<TTypes...>						MOtherFields;

	public:
		void Print(void) const;

	public:
		CVariadicTemplateClass1(TThis This, TTypes... Others);
		virtual ~CVariadicTemplateClass1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClass1<TThis,TTypes...>::CVariadicTemplateClass1(TThis This, TTypes... Others)
	: MField(This), MOtherFields(Others...)
{
	std::wcout << L"CVariadicTemplateClass1<TThis,TTypes...> - CONSTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClass1<TThis,TTypes...>::~CVariadicTemplateClass1(void) noexcept
{
	std::wcout << L"CVariadicTemplateClass1<TThis,TTypes...> - DESTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
void CVariadicTemplateClass1<TThis,TTypes...>::Print(void) const
{
	// !!! Vypise sa 1. FIELD.
	std::wcout << L"CVariadicTemplateClass1<TThis,TTypes...> - VALUE [" << MField << L"] !" << std::endl;

	// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych FIELDS.
	MOtherFields.Print();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre koniec RECURSION.
template<>
class CVariadicTemplateClass1<> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;

	public:
		CVariadicTemplateClass1(void);
		virtual ~CVariadicTemplateClass1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! CONSTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass1<>].
CVariadicTemplateClass1<>::CVariadicTemplateClass1(void)
{
	std::wcout << L"CVariadicTemplateClass1<> - CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DESTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! DESTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass1<>].
CVariadicTemplateClass1<>::~CVariadicTemplateClass1(void) noexcept
{
	std::wcout << L"CVariadicTemplateClass1<> - DESTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre koniec RECURSION.
// !!!!! METHOD je definovana pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass1<>].
void CVariadicTemplateClass1<>::Print(void) const
{
	std::wcout << L"CVariadicTemplateClass1<> - END of PRINT METHOD !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------