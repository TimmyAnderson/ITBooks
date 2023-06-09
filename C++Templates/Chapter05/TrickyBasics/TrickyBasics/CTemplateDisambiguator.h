//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateDisambiguator final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		template<typename TOtherType>
		TOtherType ConvertValue(void) const;

	public:
		CTemplateDisambiguator(const TType& Value);
		virtual ~CTemplateDisambiguator(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateDisambiguator<TType>::CTemplateDisambiguator(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateDisambiguator<TType>::~CTemplateDisambiguator(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateDisambiguator<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TOtherType>
TOtherType CTemplateDisambiguator<TType>::ConvertValue(void) const
{
	const TType&												OriginalValue=MValue;
	TOtherType													ConvertedValue=static_cast<TOtherType>(OriginalValue);

	return(ConvertedValue);
}
//----------------------------------------------------------------------------------------------------------------------