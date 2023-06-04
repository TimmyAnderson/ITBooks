//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CValue final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		CValue& operator=(const CValue& Other);
		CValue& operator=(CValue&& Other) noexcept;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CValue(void);
		CValue(const TType& Value);
		CValue(const CValue& Other);
		CValue(CValue&& Other) noexcept;
		~CValue(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>::CValue(void)
	: MValue(0)
{
	std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>::CValue(const TType& Value)
	: MValue(Value)
{
	std::wcout << L"CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>::CValue(const CValue<TType>& Other)
	: MValue(Other.MValue)
{
	std::wcout << L"COPY CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>::CValue(CValue<TType>&& Other) noexcept
	: MValue(std::move(Other.MValue))
{
	std::wcout << L"MOVE CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>::~CValue(void)
{
	std::wcout << L"DESTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>& CValue<TType>::operator=(const CValue<TType>& Other)
{
	MValue=Other.MValue;

	std::wcout << L"COPY OPERATOR= CALLED for VALUE [" << MValue << L"] !" << std::endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CValue<TType>& CValue<TType>::operator=(CValue<TType>&& Other) noexcept
{
	MValue=std::move(Other.MValue);

	std::wcout << L"MOVE OPERATOR= CALLED for VALUE [" << MValue << L"] !" << std::endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CValue<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
std::wostream& operator<<(std::wostream& Stream, const CValue<TType>& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------