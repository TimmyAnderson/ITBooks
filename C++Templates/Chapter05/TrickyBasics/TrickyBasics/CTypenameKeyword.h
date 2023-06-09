//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTypenameKeyword final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Kedze IDENTIFIER 'TType::TInternalType' pouziva TEMPLATE PARAMETER 'TType' a zaroven definuje TYPE, je NUTNE pouzit KEYWORD [typename].
		// !!! TYPE 'TType' MUSI definovat TYPE 'TInternalType'.
		typename TType::TInternalType							MValue;

	public:
		TType GetValue(void) const noexcept;

	public:
		CTypenameKeyword(const TType& Value);
		virtual ~CTypenameKeyword(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTypenameKeyword<TType>::CTypenameKeyword(const TType& Value)
	: MValue(Value.GetValue())
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTypenameKeyword<TType>::~CTypenameKeyword(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType CTypenameKeyword<TType>::GetValue(void) const noexcept
{
	TType														Value(MValue);

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------