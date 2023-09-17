//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CParsingDependentNamesUsingBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CParsingDependentNamesUsingDerived1 final : private CParsingDependentNamesUsingBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! Do CLASS SCOPE sa vlozi USING z BASE CLASS.
		// !!!!! Kedze NAME [CParsingDependentNamesUsingBase<TType>] je DEPENDENT NAME, je NUTNE pouzit KEYWORD [typename].
		using													typename CParsingDependentNamesUsingBase<TType>::BASE_TYPE;

	private:
		BASE_TYPE												MValue;

	public:
		const BASE_TYPE& GetValue(void) const noexcept;

	public:
		CParsingDependentNamesUsingDerived1(const BASE_TYPE& Value);
		virtual ~CParsingDependentNamesUsingDerived1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesUsingDerived1<TType>::CParsingDependentNamesUsingDerived1(const BASE_TYPE& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesUsingDerived1<TType>::~CParsingDependentNamesUsingDerived1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const typename CParsingDependentNamesUsingDerived1<TType>::BASE_TYPE& CParsingDependentNamesUsingDerived1<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------