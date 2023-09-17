//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CParsingDependentNamesUsingBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													BASE_TYPE=TType;
	
	public:
		template<typename TInnerType>
		class CParsingDependentNamesUsingBaseInner final
		{
//----------------------------------------------------------------------------------------------------------------------
			private:
				TInnerType										MValue;
			
			public:
				const TInnerType& GetValue(void) const noexcept;

			public:
				CParsingDependentNamesUsingBaseInner(const TInnerType& Value);
				virtual ~CParsingDependentNamesUsingBaseInner(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TInnerType>
CParsingDependentNamesUsingBase<TType>::CParsingDependentNamesUsingBaseInner<TInnerType>::CParsingDependentNamesUsingBaseInner(const TInnerType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TInnerType>
CParsingDependentNamesUsingBase<TType>::CParsingDependentNamesUsingBaseInner<TInnerType>::~CParsingDependentNamesUsingBaseInner(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TInnerType>
const TInnerType& CParsingDependentNamesUsingBase<TType>::CParsingDependentNamesUsingBaseInner<TInnerType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------