//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeFunctionIsSame.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct SSFINAETraitIsDefaultConstructible final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! 1. DECLARATION OVERLOADED TEMPLATE METHOD. V DEFAULT ARGUMENT 2. TEMPLATE PARAMETER obsahuje CODE, ktory testuje ci TYPE [TLocalType] ma DEFAULT CONSTRUCTOR.
	    // !!!!! 1. DECLARATION OVERLOADED TEMPLATE METHOD vracia RETURN VALUE TYPE [int]. RETURN VALUE TYPE sluzi na urcenie, ktora TEST METHOD bola COMPILER vybrana.
		// !!!!! DECLARATION OVERLOADED TEMPLATE METHOD NESMIE pouzit TEMPLATE PARAMETER [TType] z TEMPLATE CLASS, inak by COMPILER namiesto aplikovania SFINAE generoval COMPILATION ERROR.
		template<typename TLocalType, typename=decltype(TLocalType())>
		static int TraitTest(void*);

		// !!!!! 2. DECLARATION OVERLOADED TEMPLATE METHOD. Ako PARAMETER ma ELLIPSIS, aby bola VZDY horsim MATCH ako 1. DECLARATION OVERLOADED TEMPLATE METHOD.
	    // !!!!! 2. DECLARATION OVERLOADED TEMPLATE METHOD vracia RETURN VALUE TYPE [double]. RETURN VALUE TYPE sluzi na urcenie, ktora TEST METHOD bola COMPILER vybrana.
		template<typename>
		static double TraitTest(...);

	public:
		// !!!!! TYPE TRAIT VARIABLE vola DECLARATIONS OVERLOADED TEMPLATE METHODS a nechava COMPILER vybrat tu na zaklade toho ci TYPE [TType] ma DEFAULT CONSTRUCTOR.
		static constexpr bool									VALUE=STypeFunctionIsSame<decltype(TraitTest<TType>(nullptr)),int>::VALUE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------