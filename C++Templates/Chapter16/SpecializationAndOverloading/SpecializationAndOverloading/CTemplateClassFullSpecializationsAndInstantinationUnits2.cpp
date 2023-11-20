//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION PRIMARY TEMPLATE CLASS.
template<typename TType>
class CTemplateClassFullSpecializationsAndInstantinationUnits;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je TEMPLATE CLASS SPECIALIZATION.
// !!!!! TEMPLATE CLASS SPECIALIZATION je definovana v INOM TRANSLATION UNIT ako PRIMARY TEMPLATE CLASS.
template<>
class CTemplateClassFullSpecializationsAndInstantinationUnits<double> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr int									VALUE=200;

	private:
		double													MValue;

	public:
		void Print(void) const;

	public:
		CTemplateClassFullSpecializationsAndInstantinationUnits(double Value);
		virtual ~CTemplateClassFullSpecializationsAndInstantinationUnits(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTemplateClassFullSpecializationsAndInstantinationUnits<double>::CTemplateClassFullSpecializationsAndInstantinationUnits(double Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CTemplateClassFullSpecializationsAndInstantinationUnits<double>::~CTemplateClassFullSpecializationsAndInstantinationUnits(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CTemplateClassFullSpecializationsAndInstantinationUnits<double>::Print(void) const
{
	std::wcout << L"UNITS - TEMPLATE CLASS SPECIALIZATION - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassFullSpecializationsAndInstantinationUnits2(void)
{
	CTemplateClassFullSpecializationsAndInstantinationUnits<double>	Object(123.456);

	Object.Print();

	std::wcout << L"UNITS - TEMPLATE CLASS SPECIALIZATION - VALUE [" << CTemplateClassFullSpecializationsAndInstantinationUnits<double>::VALUE << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------