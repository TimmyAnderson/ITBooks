//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CTuple.h"
#include "CValueList.h"
#include "CMakeIndexListType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je CALLBACK FUNCTION, 2. TEMPLATE PARAMETER su TYPES TUPLE ELEMENTS a 3. TEMPLATE PARAMETER je zoznam INDEXES, ktorych FIELD VALUES sa maju vybrat z TUPLE.
template<typename TCallback, typename... TTupleElements, size_t... INDICES>
auto TupleApplyInternal(TCallback Callback, const CTuple<TTupleElements...>& Tuple, CValueList<size_t,INDICES...>) ->decltype(Callback(TupleGet<INDICES>(Tuple)...))
{
	return(Callback(TupleGet<INDICES>(Tuple)...));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je CALLBACK FUNCTION, 2. TEMPLATE PARAMETER su TYPES TUPLE ELEMENTS a 3. TEMPLATE PARAMETER urcuje pocet FIELDS v TUPLE.
template<typename TCallback, typename... TTupleElements, size_t NUMBER_OF_ELEMENTS=sizeof...(TTupleElements)>
auto TupleApply(TCallback Callback, const CTuple<TTupleElements...>& Tuple) ->decltype(TupleApplyInternal(Callback,Tuple,CMakeIndexList<NUMBER_OF_ELEMENTS>()))
{
	return(TupleApplyInternal(Callback,Tuple,CMakeIndexList<NUMBER_OF_ELEMENTS>()));
}
//----------------------------------------------------------------------------------------------------------------------