//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
#include "CCustomEnableIf.h"
//-------------------------------------------------------------------------------------------------------
class CCustomEnableIf
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		template<typename TType>
		typename CEnableIf<std::is_class<TType>::value,TType>::TYPE EnableIfInReturnValue(TType Value)
		{
			typename CEnableIf<std::is_class<TType>::value,TType>::TYPE	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}

		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		template<typename TType>
		TType EnableIfInParameter(typename CEnableIf<std::is_class<TType>::value,TType>::TYPE Value)
		{
			typename CEnableIf<std::is_class<TType>::value,TType>::TYPE	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}

		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		// !!! 2. PARAMETER je ANONYMOUS. Pouziva sa iba na testovanie ci [TType] je CLASS.
		template<typename TType, typename =typename CEnableIf<std::is_class<TType>::value,TType>::TYPE>
		TType EnableIfInTypeParameter(TType Value)
		{
			typename CEnableIf<std::is_class<TType>::value,TType>::TYPE	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------