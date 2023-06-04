//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale NIE DEFINITION VARIADIC TEMPLATE CLASS.
template<typename... TTypes>
class CVariadicClassNoFinalCase;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
class CVariadicClassNoFinalCase<TThis,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Obsahuje 1. TEMPLATE PARAMETER.
		TThis													MField;
		// !!! Obsahuje CLASS 'CVariadicClassNoFinalCase<>', ktora uklada <2,N> TEMPLATE PARAMETER.
		CVariadicClassNoFinalCase<TTypes...>					MOtherFields;

	public:
		void Print(void) const;

	public:
		CVariadicClassNoFinalCase(TThis This, TTypes... Others);
		virtual ~CVariadicClassNoFinalCase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicClassNoFinalCase<TThis,TTypes...>::CVariadicClassNoFinalCase(TThis This, TTypes... Others)
	: MField(This), MOtherFields(Others...)
{
	std::wcout << L"CVariadicClassNoFinalCase<TThis,TTypes...> - CONSTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
CVariadicClassNoFinalCase<TThis,TTypes...>::~CVariadicClassNoFinalCase(void) noexcept
{
	std::wcout << L"CVariadicClassNoFinalCase<TThis,TTypes...> - DESTRUCTOR CALLED - VALUE [" << MField << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre kazdu RECURSION.
template<typename TThis, typename... TTypes>
void CVariadicClassNoFinalCase<TThis,TTypes...>::Print(void) const
{
	// !!! Vypise sa 1. FIELD.
	std::wcout << L"CVariadicClassNoFinalCase<TThis,TTypes...> - VALUE [" << MField << L"] !" << std::endl;

	// !!!!! Pouziva sa KEYWORD [if constexpr] na urcenie ci sa ma KOMPILOVAT IF BLOCK, alebo ELSE BLOCK.
	if constexpr (sizeof...(TTypes)>0)
	{
		// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych FIELDS.
		MOtherFields.Print();
	}
	else
	{
		std::wcout << L"CVariadicClassNoFinalCase<TThis,TTypes...> - END of PRINT METHOD !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je VARIADIC TEMPLATE CLASS SPECIALIZATION pre koniec RECURSION.
template<>
class CVariadicClassNoFinalCase<> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CVariadicClassNoFinalCase(void);
		virtual ~CVariadicClassNoFinalCase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! CONSTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicClassNoFinalCase<>].
CVariadicClassNoFinalCase<>::CVariadicClassNoFinalCase(void)
{
	std::wcout << L"CVariadicClassNoFinalCase<> - CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DESTRUCTOR pouzivany pre koniec RECURSION.
// !!!!! DESTRUCTOR je definovany pre TEMPLATE SPECIALIZATION [CVariadicClassNoFinalCase<>].
CVariadicClassNoFinalCase<>::~CVariadicClassNoFinalCase(void) noexcept
{
	std::wcout << L"CVariadicClassNoFinalCase<> - DESTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------