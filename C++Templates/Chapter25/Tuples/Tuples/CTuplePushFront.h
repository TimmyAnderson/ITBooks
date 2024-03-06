//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTuple.h"
#include "CTupleTypeListInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER su TYPES TUPLE ELEMEMNTS a 2. TEMPLATE PARAMETER je TYPE noveho ELEMENT.
template<typename... TTupleElements, typename TNewElement>
CTupleTypeListPushFrontType<CTuple<TTupleElements...>,TNewElement>::TYPE
TuplePushFront(const CTuple<TTupleElements...>& Tuple, const TNewElement& Value)
{
	typename CTupleTypeListPushFrontType<CTuple<TTupleElements...>,TNewElement>::TYPE	Result(Value,Tuple);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------