//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Od verzie C++17 je mozne definovat VARIADIC TEMPLATE CLASS pre koniec RECURSION nie s 0 TEMPLATE PARAMETERS, ale s 1 TEMPLATE PARAMETER. V pripade pouzitia VARIADIC TEMPLATE CLASS s 1 TEMPLATE PARAMETER je pouzita TEMPLATE CLASS SPECIALIZATION s 1 TEMPLATE PARAMETER a nie TEMPLATE CLASS SPECIALIZATION obsahujuca TEMPLATE PARAMETER PACK.
// !!! DECLARATION, ale NIE DEFINITION VARIADIC TEMPLATE CLASS.
template<typename... TTypes>
class CVariadicTemplateClass2;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
class CVariadicTemplateClass2<TThis,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Obsahuje 1. TEMPLATE PARAMETER.
		TThis													MField;
		// !!! Obsahuje CLASS 'CVariadicTemplateClass2<>', ktora uklada <2,N> TEMPLATE PARAMETER.
		CVariadicTemplateClass2<TTypes...>						MOtherFields;

	public:
		void Print(void) const;

	public:
		CVariadicTemplateClass2(TThis This, TTypes... Others);
		virtual ~CVariadicTemplateClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClass2<TThis,TTypes...>::CVariadicTemplateClass2(TThis This, TTypes... Others)
	: MField(This), MOtherFields(Others...)
{
	std::wcout << L"CVariadicTemplateClass2<TThis,TTypes...> - CONSTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicTemplateClass2<TThis,TTypes...>::~CVariadicTemplateClass2(void) noexcept
{
	std::wcout << L"CVariadicTemplateClass2<TThis,TTypes...> - DESTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
void CVariadicTemplateClass2<TThis,TTypes...>::Print(void) const
{
	// !!! Vypise sa 1. FIELD.
	std::wcout << L"CVariadicTemplateClass2<TThis,TTypes...> - VALUE [" << MField << L"] !" << std::endl;

	// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych FIELDS.
	MOtherFields.Print();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Od verzie C++17 je mozne definovat VARIADIC TEMPLATE CLASS pre koniec RECURSION nie s 0 TEMPLATE PARAMETERS, ale s 1 TEMPLATE PARAMETER. V pripade pouzitia VARIADIC TEMPLATE CLASS s 1 TEMPLATE PARAMETER je pouzita TEMPLATE CLASS SPECIALIZATION s 1 TEMPLATE PARAMETER a nie TEMPLATE CLASS SPECIALIZATION obsahujuca TEMPLATE PARAMETER PACK.
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre koniec RECURSION.
// !!!!! KONIEC RECURSION je ak ma TEMPLATE CLASS iba 1 TEMPLATE PARAMETER.
template<typename TThis>
class CVariadicTemplateClass2<TThis> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Obsahuje TEMPLATE PARAMETER.
		TThis													MField;

	public:
		void Print(void) const;

	public:
		CVariadicTemplateClass2(TThis This);
		virtual ~CVariadicTemplateClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! CONSTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass2<TThis>].
template<typename TThis>
CVariadicTemplateClass2<TThis>::CVariadicTemplateClass2(TThis This)
	: MField(This)
{
	std::wcout << L"CVariadicTemplateClass2<TThis> - CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DESTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! DESTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass2<TThis>].
template<typename TThis>
CVariadicTemplateClass2<TThis>::~CVariadicTemplateClass2(void) noexcept
{
	std::wcout << L"CVariadicTemplateClass2<TThis> - DESTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre koniec RECURSION.
// !!!!! METHOD je definovana pre TEMPLATE SPECIALIZATION [CVariadicTemplateClass2<TThis>].
template<typename TThis>
void CVariadicTemplateClass2<TThis>::Print(void) const
{
	std::wcout << L"CVariadicTemplateClass2<TThis> - VALUE [" << MField << L"] !" << std::endl;

	std::wcout << L"END of PRINT METHOD !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------