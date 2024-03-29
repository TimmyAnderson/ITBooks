//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CTupleEBCOElement.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CTupleEBCO;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
TType& GetElementID(CTupleEBCOElement<ELEMENT_ID,TType>& TupleElement)
{
	TType&														Result=TupleElement.Get();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t INDEX, typename... TTupleElements>
auto TupleGetFast(CTupleEBCO<TTupleElements...>& Tuple) -> decltype(GetElementID<sizeof...(TTupleElements)-INDEX-1>(Tuple))
{
	// !!!!! C++ CONVERSION z TUPLE [Tuple] na BASE CLASS [CTupleEBCOElement<ELEMENT_ID,TType>] vykonava C++ automaticky priamym LOOKUP pri zlozitosti (1) a teda nie je nutne rekurzivne prechadzat vsetky TUPLE ELEMENTS.
	return(GetElementID<sizeof...(TTupleElements)-INDEX-1>(Tuple));
}
//----------------------------------------------------------------------------------------------------------------------