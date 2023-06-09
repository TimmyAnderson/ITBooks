//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CZeroInitialization final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue1;
		TType													MValue2;
		// !!! Rozlicne sposoby vykonania ZERO INITIALIZATION.
		TType													MValue3=TType();
		TType													MValue4{};

	public:
		const TType& GetValue1(void) const noexcept;
		const TType& GetValue2(void) const noexcept;
		const TType& GetValue3(void) const noexcept;
		const TType& GetValue4(void) const noexcept;

	public:
		CZeroInitialization(void);
		virtual ~CZeroInitialization(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Rozlicne sposoby vykonania ZERO INITIALIZATION.
template<typename TType>
CZeroInitialization<TType>::CZeroInitialization(void)
	: MValue1(), MValue2{}
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CZeroInitialization<TType>::~CZeroInitialization(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CZeroInitialization<TType>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CZeroInitialization<TType>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CZeroInitialization<TType>::GetValue3(void) const noexcept
{
	return(MValue3);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CZeroInitialization<TType>::GetValue4(void) const noexcept
{
	return(MValue4);
}
//----------------------------------------------------------------------------------------------------------------------