//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
class CStandardEnableIf
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		template<typename TType>
		typename std::enable_if<std::is_class<TType>::value,TType>::type EnableIfInReturnValue(TType Value)
		{
			typename std::enable_if<std::is_class<TType>::value,TType>::type	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}

		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		template<typename TType>
		TType EnableIfInParameter(typename std::enable_if<std::is_class<TType>::value,TType>::type Value)
		{
			typename std::enable_if<std::is_class<TType>::value,TType>::type	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}

		// !!! TEMPLATE METHOD je definovana IBA pre CLASS TYPES.
		// !!! 2. PARAMETER je ANONYMOUS. Pouziva sa iba na testovanie ci [TType] je CLASS.
		template<typename TType, typename =typename std::enable_if<std::is_class<TType>::value,TType>::type>
		TType EnableIfInTypeParameter(TType Value)
		{
			typename std::enable_if<std::is_class<TType>::value,TType>::type	JustOneMoreCopy=Value;

			return(JustOneMoreCopy);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------