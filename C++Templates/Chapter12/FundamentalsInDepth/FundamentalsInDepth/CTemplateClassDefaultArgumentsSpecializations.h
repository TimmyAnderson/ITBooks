//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDefaultArgumentsSpecializations final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		void Print(void) const;

	public:
		CTemplateClassDefaultArgumentsSpecializations(TType1 Field1, TType2 Field2);
		virtual ~CTemplateClassDefaultArgumentsSpecializations(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsSpecializations<TType1,TType2>::CTemplateClassDefaultArgumentsSpecializations(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsSpecializations<TType1,TType2>::~CTemplateClassDefaultArgumentsSpecializations(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CTemplateClassDefaultArgumentsSpecializations<TType1,TType2>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE CLASS PARTIAL SPECIALIZATIONS NESMU mat DEFAULT TEMPLATE ARGUMENTS.
//template<typename TType=double>
template<typename TType>
class CTemplateClassDefaultArgumentsSpecializations<TType,int> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField1;
		int														MField2;

	public:
		void Print(void) const;

	public:
		CTemplateClassDefaultArgumentsSpecializations(TType Field1, int Field2);
		virtual ~CTemplateClassDefaultArgumentsSpecializations(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDefaultArgumentsSpecializations<TType,int>::CTemplateClassDefaultArgumentsSpecializations(TType Field1, int Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDefaultArgumentsSpecializations<TType,int>::~CTemplateClassDefaultArgumentsSpecializations(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateClassDefaultArgumentsSpecializations<TType,int>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS SPECIALIZATION - FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------