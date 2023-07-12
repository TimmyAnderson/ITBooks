//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CClassWithConversionConstructor final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! CLASS drzi iba POINTER, ale NEVYKONAVA COPY VALUES v POINTER.
		const TType*											MValue;

	public:
		const TType* GetValue(void) const noexcept;

	public:
		// !!! CONVERSION CONSTRUCTOR.
		CClassWithConversionConstructor(const TType* Value);
		virtual ~CClassWithConversionConstructor(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithConversionConstructor<TType>::CClassWithConversionConstructor(const TType* Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithConversionConstructor<TType>::~CClassWithConversionConstructor(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType* CClassWithConversionConstructor<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------