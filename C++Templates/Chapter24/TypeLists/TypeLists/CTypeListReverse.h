//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
#include "CTypeListIsEmpty.h"
#include "CTypeListFront.h"
#include "CTypeListPushBack2.h"
#include "CTypeListPopFront.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST a 2. TEMPLATE PARAMETER urcuje ci TYPE LIST je EMPTY.
template<typename TTypeList, bool EMPTY=CTypeListIsEmpty<TTypeList>>
class CTypeListReverseType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATION vlozi FRONT na koniec TYPE LIST z ktoreho odstrani posledny ITEM. OPERATION sa vykonava rekurzivne.
template<typename TTypeList>
class CTypeListReverseType<TTypeList,false> : public CTypeListPushBack2Type<typename CTypeListReverseType<CTypeListPopFront<TTypeList>>::TYPE,CTypeListFront<TTypeList>>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList>
class CTypeListReverseType<TTypeList,true>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TTypeList;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList>
using															CTypeListReverse=typename CTypeListReverseType<TTypeList>::TYPE;
//----------------------------------------------------------------------------------------------------------------------