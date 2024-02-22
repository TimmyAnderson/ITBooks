//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST a 2. TEMPLATE PARAMETER je novy TYPE, ktory ma byt do TYPE LIST pridany.
template<typename TTypeList, typename TNewType>
class CTypeListPushFrontType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypeListElements, typename TNewType>
class CTypeListPushFrontType<CTypeList<TTypeListElements...>,TNewType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! Vytvori sa novy TYPE LIST, ktory ma na zaciatok TYPES pridany novy TYPE.
		using													TYPE=CTypeList<TNewType,TTypeListElements...>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, typename TNewType>
using															CTypeListPushFront=typename CTypeListPushFrontType<TTypeList,TNewType>::TYPE;
//----------------------------------------------------------------------------------------------------------------------