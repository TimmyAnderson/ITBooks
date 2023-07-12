//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CComplexTemplate.h"
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CFriendlyTemplate
{
//-------------------------------------------------------------------------------------------------------
	public:
		TType GetPrivateMember(const CComplexTemplate<TType>& Value)
		{
			// !!! Moze vracat PRIVATE MEMBER, pretoze je FRIEND CLASS voci CComplexTemplate.
			return(Value.MPrivateMember);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------