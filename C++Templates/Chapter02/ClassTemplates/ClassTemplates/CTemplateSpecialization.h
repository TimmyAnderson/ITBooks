//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstddef>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateSpecialization
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		TType Get(void) const noexcept;
		void Set(TType Value) noexcept;

	public:
		CTemplateSpecialization(void)
			: MValue()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType CTemplateSpecialization<TType>::Get(void) const noexcept
{
	std::wcout << L"TEMPLATE METHOD [TType Get(void) const noexcept] CALLED !" << std::endl;

	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateSpecialization<TType>::Set(TType Value) noexcept
{
	std::wcout << L"TEMPLATE METHOD [void Set(TType Value) noexcept] CALLED !" << std::endl;

	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre TYPE [wstring].
template<>
class CTemplateSpecialization<std::wstring>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		// !!!!! PROTOTYPE TEMPLATE SPECIALIZATION METHODS MOZE BYT INY ako v povodnej TEMPLATE CLASS.
		const std::wstring& Get(void) const noexcept;
		void Set(const std::wstring& Value) noexcept;

	public:
		// !!!!! TEMPLATE SPECIALIZATION moze obsahovat aj dodatocne METHODS.
		std::size_t GetLength(void) const noexcept;

	public:
		CTemplateSpecialization(void)
			: MValue()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PROTOTYPE TEMPLATE SPECIALIZATION METHODS MOZE BYT INY ako v povodnej TEMPLATE CLASS.
const std::wstring& CTemplateSpecialization<std::wstring>::Get(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [const std::wstring& Get(void) const noexcept] CALLED !" << std::endl;

	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PROTOTYPE TEMPLATE SPECIALIZATION METHODS MOZE BYT INY ako v povodnej TEMPLATE CLASS.
void CTemplateSpecialization<std::wstring>::Set(const std::wstring& Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set(const std::wstring& Value) noexcept] CALLED !" << std::endl;

	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION moze obsahovat aj dodatocne METHODS.
std::size_t CTemplateSpecialization<std::wstring>::GetLength(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [std::size_t GetLength(void) const noexcept] CALLED !" << std::endl;

	std::size_t													Length=MValue.size();

	return(Length);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Je to SPECIALIZATION TEMPLATE METHOD pre TYPE [double] bez toho, aby sa pre TYPE [double] vykonala SPECIALIZATION TEMPLATE CLASS.
template<>
double CTemplateSpecialization<double>::Get(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [double Get(void) const noexcept] CALLED !" << std::endl;

	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Je to SPECIALIZATION TEMPLATE METHOD pre TYPE [double] bez toho, aby sa pre TYPE [double] vykonala SPECIALIZATION TEMPLATE CLASS.
template<>
void CTemplateSpecialization<double>::Set(double Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set(double Value) noexcept] CALLED !" << std::endl;

	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------