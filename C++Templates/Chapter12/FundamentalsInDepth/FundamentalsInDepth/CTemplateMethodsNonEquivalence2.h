//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateMethodsNonEquivalence2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		template<typename TType>
		CTemplateMethodsNonEquivalence2(const TType& Value);
		CTemplateMethodsNonEquivalence2(const CTemplateMethodsNonEquivalence2&& Value) noexcept;
		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateMethodsNonEquivalence2(const volatile CTemplateMethodsNonEquivalence2&)=delete;
		virtual ~CTemplateMethodsNonEquivalence2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethodsNonEquivalence2::CTemplateMethodsNonEquivalence2(const TType& Value)
	: MValue()
{
	if constexpr (std::is_same<TType,CTemplateMethodsNonEquivalence2>::value)
	{
		MValue=Value.GetValue();
	}
	else
	{
		MValue=Value;
	}

	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------