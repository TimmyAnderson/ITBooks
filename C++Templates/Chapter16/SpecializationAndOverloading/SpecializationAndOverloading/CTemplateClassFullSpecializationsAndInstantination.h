//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je PRIMARY TEMPLATE CLASS.
template<typename TType>
class CTemplateClassFullSpecializationsAndInstantination final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		void PrintPrimaryTemplate(void) const;

	public:
		CTemplateClassFullSpecializationsAndInstantination(TType Value);
		virtual ~CTemplateClassFullSpecializationsAndInstantination(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassFullSpecializationsAndInstantination<TType>::CTemplateClassFullSpecializationsAndInstantination(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassFullSpecializationsAndInstantination<TType>::~CTemplateClassFullSpecializationsAndInstantination(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateClassFullSpecializationsAndInstantination<TType>::PrintPrimaryTemplate(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
inline void TemplateClassFullSpecializationsAndInstantinationTest(void)
{
	{
		// !!!!! Pouzije sa PRIMARY TEMPLATE.
		CTemplateClassFullSpecializationsAndInstantination<int>	Object(100);

		Object.PrintPrimaryTemplate();
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze pri pouziti CLASS [CTemplateClassFullSpecializationsAndInstantination<double>] sa najprv vytvori INSTANTINATION, no az NASLEDNE je definovana SPECIALIZATION [CTemplateClassFullSpecializationsAndInstantination<double>], co je ERROR. INSTANTINATION z TEMPLATE SPECIALIZATIONS sa MUSIA vykonat AZ POTOM, co su tieto TEMPLATE SPECIALIZATIONS DEFINED.
		CTemplateClassFullSpecializationsAndInstantination<double>	Object(123.456);

		Object.PrintPrimaryTemplate();
	}
	*/
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je TEMPLATE CLASS SPECIALIZATION.
template<>
class CTemplateClassFullSpecializationsAndInstantination<double> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		double													MValue;

	public:
		void PrintPrimaryTemplate(void) const;

	public:
		CTemplateClassFullSpecializationsAndInstantination(double Value);
		virtual ~CTemplateClassFullSpecializationsAndInstantination(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------