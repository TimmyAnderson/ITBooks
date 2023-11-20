//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je PRIMARY TEMPLATE CLASS.
template<typename TType>
class CTemplateClassFullSpecializationsAndInstantinationUnits final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr int									VALUE=100;

	private:
		TType													MValue;

	public:
		void Print(void) const;

	public:
		CTemplateClassFullSpecializationsAndInstantinationUnits(TType Value);
		virtual ~CTemplateClassFullSpecializationsAndInstantinationUnits(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassFullSpecializationsAndInstantinationUnits<TType>::CTemplateClassFullSpecializationsAndInstantinationUnits(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassFullSpecializationsAndInstantinationUnits<TType>::~CTemplateClassFullSpecializationsAndInstantinationUnits(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateClassFullSpecializationsAndInstantinationUnits<TType>::Print(void) const
{
	std::wcout << L"UNITS - PRIMARY TEMPLATE CLASS - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsAndInstantinationUnits1(void)
{
	{
		// !!!!! Pouziva sa PRIMARY TEMPLATE.
		CTemplateClassFullSpecializationsAndInstantinationUnits<int>	Object(100);

		Object.Print();

		std::wcout << L"UNITS - TEMPLATE CLASS SPECIALIZATION - VALUE [" << CTemplateClassFullSpecializationsAndInstantinationUnits<int>::VALUE << L"]." << std::endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze sa pouziva TEMPLATE SPECIALIZATION [CTemplateClassFullSpecializationsAndInstantinationUnits<double>], ktora je vsak DEFINED v INOM TRANSLATION UNIT [CTemplateClassFullSpecializationsAndInstantinationUnits2.cpp].
		// !!!!! G++ ERROR NEHODI, co je ale CHYBA COMPILER.
		CTemplateClassFullSpecializationsAndInstantinationUnits<double>	Object(123.456);

		Object.Print();

		std::wcout << L"UNITS - TEMPLATE CLASS SPECIALIZATION - VALUE [" << CTemplateClassFullSpecializationsAndInstantinationUnits<double>::VALUE << L"]." << std::endl;
	}
	*/
}
//----------------------------------------------------------------------------------------------------------------------