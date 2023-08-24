//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateTemplateSpecialMethods1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		template<typename TType>
		CTemplateTemplateSpecialMethods1(const TType& Value);
		CTemplateTemplateSpecialMethods1(const CTemplateTemplateSpecialMethods1& Value);
		CTemplateTemplateSpecialMethods1(const CTemplateTemplateSpecialMethods1&& Value) noexcept;
		virtual ~CTemplateTemplateSpecialMethods1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateTemplateSpecialMethods1::CTemplateTemplateSpecialMethods1(const TType& Value)
	: MValue(Value)
{
	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------