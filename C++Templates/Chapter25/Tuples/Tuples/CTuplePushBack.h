//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTuple.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETER je TYPE noveho ELEMENT.
template<typename TNewElement>
CTuple<TNewElement> TuplePushBack(const CTuple<>&, const TNewElement& Value)
{
	CTuple<TNewElement>											Result(Value);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE TUPLE HEAD, 2. TEMPLATE PARAMETER su TYPES TUPLE TAIL a 3. TEMPLATE PARAMETER je TYPE noveho ELEMENT.
template<typename THead, typename... TTail, typename TNewElement>
CTuple<THead,TTail...,TNewElement> TuplePushBack(const CTuple<THead,TTail...>& Tuple, const TNewElement& Value)
{
	// !!! FUNCTION sa vola rekurzivne.
	CTuple<THead,TTail...,TNewElement>							Result(Tuple.GetHead(),TuplePushBack(Tuple.GetTail(),Value));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------