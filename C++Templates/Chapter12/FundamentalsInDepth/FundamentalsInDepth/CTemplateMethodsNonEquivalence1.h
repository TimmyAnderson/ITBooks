//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateMethodsNonEquivalence1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		template<typename TType>
		CTemplateMethodsNonEquivalence1(const TType& Value);
		CTemplateMethodsNonEquivalence1(const CTemplateMethodsNonEquivalence1& Value);
		CTemplateMethodsNonEquivalence1(const CTemplateMethodsNonEquivalence1&& Value) noexcept;
		virtual ~CTemplateMethodsNonEquivalence1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethodsNonEquivalence1::CTemplateMethodsNonEquivalence1(const TType& Value)
	: MValue(Value)
{
	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------