//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateMethodsNonEquivalence3 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CTemplateMethodsNonEquivalence3(const std::wstring& Value);
		template<typename TType,typename=std::enable_if<std::is_same<TType,CTemplateMethodsNonEquivalence3>::value>::type>
		CTemplateMethodsNonEquivalence3(const TType& Value);
		CTemplateMethodsNonEquivalence3(const CTemplateMethodsNonEquivalence3&& Value) noexcept;
		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateMethodsNonEquivalence3(const volatile CTemplateMethodsNonEquivalence3&)=delete;
		virtual ~CTemplateMethodsNonEquivalence3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType,typename>
CTemplateMethodsNonEquivalence3::CTemplateMethodsNonEquivalence3(const TType& Value)
	: MValue(Value.GetValue())
{
	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------