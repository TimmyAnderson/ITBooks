//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CClassWithCopyAndMove final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		CClassWithCopyAndMove& operator=(const CClassWithCopyAndMove& Other);
		CClassWithCopyAndMove& operator=(CClassWithCopyAndMove&& Other) noexcept;

	public:
		const TType& GetValue(void) const noexcept;
		void SetValue(const TType& Value) noexcept;

	public:
		CClassWithCopyAndMove(void);
		CClassWithCopyAndMove(const TType& Value);
		CClassWithCopyAndMove(const CClassWithCopyAndMove& Other);
		CClassWithCopyAndMove(CClassWithCopyAndMove&& Other) noexcept;
		~CClassWithCopyAndMove(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>::CClassWithCopyAndMove(void)
	: MValue(0)
{
	std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>::CClassWithCopyAndMove(const TType& Value)
	: MValue(Value)
{
	std::wcout << L"CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>::CClassWithCopyAndMove(const CClassWithCopyAndMove<TType>& Other)
	: MValue(Other.MValue)
{
	std::wcout << L"COPY CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>::CClassWithCopyAndMove(CClassWithCopyAndMove<TType>&& Other) noexcept
	: MValue(std::move(Other.MValue))
{
	std::wcout << L"MOVE CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>::~CClassWithCopyAndMove(void)
{
	std::wcout << L"DESTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>& CClassWithCopyAndMove<TType>::operator=(const CClassWithCopyAndMove<TType>& Other)
{
	MValue=Other.MValue;

	std::wcout << L"COPY OPERATOR= CALLED for VALUE [" << MValue << L"] !" << std::endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CClassWithCopyAndMove<TType>& CClassWithCopyAndMove<TType>::operator=(CClassWithCopyAndMove<TType>&& Other) noexcept
{
	MValue=std::move(Other.MValue);

	std::wcout << L"MOVE OPERATOR= CALLED for VALUE [" << MValue << L"] !" << std::endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CClassWithCopyAndMove<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CClassWithCopyAndMove<TType>::SetValue(const TType& Value) noexcept
{
	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
std::wostream& operator<<(std::wostream& Stream, const CClassWithCopyAndMove<TType>& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------