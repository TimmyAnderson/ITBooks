//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CPartialTemplateSpecialization1
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		TType Get(void) const noexcept;
		void Set(TType Value) noexcept;

	public:
		CPartialTemplateSpecialization1(void)
			: MValue()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType CPartialTemplateSpecialization1<TType>::Get(void) const noexcept
{
	std::wcout << L"TEMPLATE METHOD [TType Get(void) const noexcept] CALLED !" << std::endl;

	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecialization1<TType>::Set(TType Value) noexcept
{
	std::wcout << L"TEMPLATE METHOD [void Set(TType Value) noexcept] CALLED !" << std::endl;

	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Vykona sa PARTIAL SPECIALIZATION TEMPLATE CLASS pre POINTERS.
template<typename TType>
class CPartialTemplateSpecialization1<TType*>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType*													MValue;

	public:
		TType* Get(void) const noexcept;
		void Set(TType* Value) noexcept;

	public:
		CPartialTemplateSpecialization1(void)
			: MValue()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType* CPartialTemplateSpecialization1<TType*>::Get(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [TType Get(void) const noexcept] CALLED !" << std::endl;

	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecialization1<TType*>::Set(TType* Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set(TType* Value) noexcept] CALLED !" << std::endl;

	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------