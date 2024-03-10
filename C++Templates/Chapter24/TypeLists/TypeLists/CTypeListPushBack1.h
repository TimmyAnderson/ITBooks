//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST a 2. TEMPLATE PARAMETER je novy TYPE, ktory ma byt do TYPE LIST pridany.
template<typename TTypeList, typename TNewType>
class CTypeListPushBack1Type;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypeListElements, typename TNewType>
class CTypeListPushBack1Type<CTypeList<TTypeListElements...>,TNewType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=CTypeList<TTypeListElements...,TNewType>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, typename TNewType>
using															CTypeListPushBack1=typename CTypeListPushBack1Type<TTypeList,TNewType>::TYPE;
//----------------------------------------------------------------------------------------------------------------------