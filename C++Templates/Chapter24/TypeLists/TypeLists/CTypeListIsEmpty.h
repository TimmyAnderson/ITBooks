//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETER je TYPE LIST.
// !!! PRIMARY TEMPLATE CLASS pre vsetky ostatne TYPES.
template<typename TTypeList>
class CTypeListIsEmptyType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr bool									VALUE=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION pre EMTPY TYPE LIST.
template<>
class CTypeListIsEmptyType<CTypeList<>>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr bool									VALUE=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList>
constexpr bool													CTypeListIsEmpty=CTypeListIsEmptyType<TTypeList>::VALUE;
//----------------------------------------------------------------------------------------------------------------------