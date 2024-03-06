//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CTuple.h"
#include "CValueList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER su TYPES TUPLE ELEMEMNTS a 2. TEMPLATE PARAMETER su INDEXES TUPLE FIELDS, z ktorych ma byt vytvoreny novy TUPLE.
template<typename... TTupleElements, size_t... INDICES>
auto TupleSelect(const CTuple<TTupleElements...>& Tuple, CValueList<size_t,INDICES...>)
{
	auto														Result=MakeTuple(TupleGet<INDICES>(Tuple)...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------