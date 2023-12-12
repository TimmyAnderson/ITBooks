//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFrom, typename TTo>
struct SSFINAETraitIsConvertibleHelper
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! DECLARATION HELPER METHOD, ktora sluzi iba na to, ze pri jej volani COMPILER skontroluje ci je mozna CONVERSION TYPE zadaneho FUNCTION ARGUMENT [TFrom] na TYPE FUNCTION PARAMETER [TTo].
		// !!!!! Kedze METHOD sa pouziva IBA v UNEVAULUATED CONTEXT (OPERATOR [OPERATOR decltype()]), METHOD NEPOTREBUJE DEFINITION a staci jej iba DECLARATION.
		static void TestConversionInternal(TTo);

		// !!!!! METHOD vykonava v 3. TEMPLATE PARAMETER pokus o CONVERSION z z TYPE [TFrom] na TYPE [TTo]. Ak tak zlyha, cela METHOD je odstranena na zaklade principu SFINAE.
		// !!!!! Kedze METHOD sa pouziva IBA v UNEVAULUATED CONTEXT (OPERATOR [OPERATOR decltype()]), METHOD NEPOTREBUJE DEFINITION a staci jej iba DECLARATION.
		// !!!!! V 3. TEMPLATE PARAMETER sa vytvori instancia TYPE [TLocalFrom] a ta sa zasle do HELPER METHOD, ktora prijma ako FUNCTION PARAMETER TYPE [TTo], cim COMPILER otestuje ci dana CONVERSION existuje.
		template<typename TLocalFrom, typename=decltype(TestConversionInternal(std::declval<TLocalFrom>()))>
		static TypeFunctionTrueType TestConversion(void*);

		// !!!!! FALLBACK METHOD, ktora sa vola ak CONVERSION z TYPE [TFrom] na TYPE [TTo] NEEXISTUJE a 1. VERSION METHOD je odstranena na zakladne principu SFINAE.
		// !!!!! Kedze METHOD sa pouziva IBA v UNEVAULUATED CONTEXT (OPERATOR [OPERATOR decltype()]), METHOD NEPOTREBUJE DEFINITION a staci jej iba DECLARATION.
		template<typename>
		static TypeFunctionFalseType TestConversion(...);

	public:
		using													TYPE=decltype(TestConversion<TFrom>(nullptr));
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFrom, typename TTo>
struct SSFINAETraitIsConvertible final : SSFINAETraitIsConvertibleHelper<TFrom,TTo>::TYPE
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFrom, typename TTo>
using															SFINAETraitIsConvertibleType=typename SSFINAETraitIsConvertible<TFrom,TTo>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFrom, typename TTo>
constexpr bool													SFINAETraitIsConvertibleValue=SSFINAETraitIsConvertible<TFrom,TTo>::VALUE;
//----------------------------------------------------------------------------------------------------------------------