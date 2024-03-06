//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "STraitsIfThenElse.h"
#include "CMakeIndexListType.h"
#include "CTuple.h"
#include "CTupleFindElement.h"
#include "CTupleSelect.h"
#include "CValueList.h"
#include "CCompileTimeValue.h"
#include "CTupleInsertionSort.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, template<typename, typename> class TFunction>
class CGetElementValue
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		template<typename TType1, typename TType2>
		class CApply;

	public:
		// !!!!! Nastavuje VALUE 'VALUE' na vysledok porovnania TYPE [CTupleFindElement<TTuple,INDEX_1>] a TYPE [CTupleFindElement<TTuple,INDEX_2>] pomocou COMPARE TYPE [TFunction].
		template<size_t INDEX_1, size_t INDEX_2>
		class CApply<CCompileTimeValue<size_t,INDEX_2>,CCompileTimeValue<size_t,INDEX_1>> : public TFunction<CTupleFindElement<TTuple,INDEX_2>,CTupleFindElement<TTuple,INDEX_1>> 
		{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<template<typename,typename> class TCompare, typename... TTupleElements>
auto TupleSort(const CTuple<TTupleElements...>& Tuple)
{
	auto														Result=TupleSelect(Tuple,CTupleInsertionSort<CMakeIndexList<sizeof...(TTupleElements)>,CGetElementValue<CTuple<TTupleElements...>,TCompare>::template CApply>());

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------