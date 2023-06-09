//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateMethods final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:	
		// !!! CONVERSION OPERATOR, ktory ma zaroven vlastny TEMPLATE PARAMETER, nezavisly na TEMPLATE PARAMETER TEMPLATE CLASS.
		template<typename TOtherType>
		CTemplateMethods<TType>& operator=(const CTemplateMethods<TOtherType>& Other);

	public:
		const TType& Get(void) const noexcept;

	public:	
		CTemplateMethods(const TType& Value);
		virtual ~CTemplateMethods(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethods<TType>::CTemplateMethods(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethods<TType>::~CTemplateMethods(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETERS TEMPLATE CLASS.
template<typename TType>
// !!! TEMPLATE PARAMETERS TEMPLATE METHOD (OPERATOR).
template<typename TOtherType>
CTemplateMethods<TType>& CTemplateMethods<TType>::operator=(const CTemplateMethods<TOtherType>& Other)
{
	const TOtherType&											OriginalValue=Other.Get();
	TType														ConvertedValue=static_cast<TType>(OriginalValue);

	MValue=ConvertedValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateMethods<TType>::Get(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------