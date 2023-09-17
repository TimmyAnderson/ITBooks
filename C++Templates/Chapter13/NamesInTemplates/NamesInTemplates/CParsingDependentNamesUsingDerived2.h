//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CParsingDependentNamesUsingBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CParsingDependentNamesUsingDerived2 final : private CParsingDependentNamesUsingBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! COMPILER hodi ERROR, pretoze tato SYNTAX NIE JE SUPPORTED.
		//using													typename CParsingDependentNamesUsingBase<TType>::template CParsingDependentNamesUsingBaseInner;

		// !!! Do CLASS SCOPE sa vlozi INNER TEMPLATE CLASS z BASE CLASS.
		// !!!!! Kedze NAME [CParsingDependentNamesUsingBase<TType>] je DEPENDENT NAME, je NUTNE pouzit KEYWORD [typename].
		// !!!!! Kedze NAME [CParsingDependentNamesUsingBaseInner<TType>] je DEPENDENT NAME TEMPLATE, je NUTNE pouzit KEYWORD [template].
		template<typename TInnerType>
		using													InnerClass=typename CParsingDependentNamesUsingBase<TType>::template CParsingDependentNamesUsingBaseInner<TType>;
		
	private:
		InnerClass<TType>										MValue;

	public:
		const InnerClass<TType>& GetValue(void) const noexcept;

	public:
		CParsingDependentNamesUsingDerived2(const InnerClass<TType>& Value);
		virtual ~CParsingDependentNamesUsingDerived2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesUsingDerived2<TType>::CParsingDependentNamesUsingDerived2(const InnerClass<TType>& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesUsingDerived2<TType>::~CParsingDependentNamesUsingDerived2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const typename CParsingDependentNamesUsingDerived2<TType>::InnerClass<TType>& CParsingDependentNamesUsingDerived2<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------