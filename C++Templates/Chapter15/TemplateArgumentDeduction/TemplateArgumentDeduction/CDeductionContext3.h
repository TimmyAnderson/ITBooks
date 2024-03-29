//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDeductionContext3 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		const TType& GetField(void) const noexcept;

	public:
		CDeductionContext3(const TType& Field);
		virtual ~CDeductionContext3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CDeductionContext3<TType>::CDeductionContext3(const TType& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CDeductionContext3<TType>::~CDeductionContext3(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CDeductionContext3<TType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------