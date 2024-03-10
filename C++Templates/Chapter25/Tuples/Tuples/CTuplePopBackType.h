//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTuple.h"
#include "CTupleTypeListInterface.h"
#include "CTupleReverseType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETER je TUPLE.
template<typename TTuple>
class CTuplePopBackType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=typename CTupleReverseType<typename CTupleTypeListPopFrontType<typename CTupleReverseType<TTuple>::TYPE>::TYPE>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------