//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CImplementationSchemes final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CImplementationSchemes(const TType& Value);
		virtual ~CImplementationSchemes(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CImplementationSchemes<TType>::CImplementationSchemes(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CImplementationSchemes<TType>::~CImplementationSchemes(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CImplementationSchemes<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ImplementationSchemesHelper(const CImplementationSchemes<int>& Value);
void ImplementationSchemesTest(void);
//----------------------------------------------------------------------------------------------------------------------