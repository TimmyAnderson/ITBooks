//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETER je TYPE LIST.
template<typename TTypeList>
class CTypeListPopFrontType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
template<>
class CTypeListPopFrontType<CTypeList<>>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=CTypeList<>;
//----------------------------------------------------------------------------------------------------------------------
};
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
class CTypeListPopFrontType<CTypeList<THead,TTail...>>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! Vytvori sa novy TYPE LIST, ktory ma zo zoznamu TYPES odstraneny prvy TYPE.
		using													TYPE=CTypeList<TTail...>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList>
using															CTypeListPopFront=typename CTypeListPopFrontType<TTypeList>::TYPE;
//----------------------------------------------------------------------------------------------------------------------