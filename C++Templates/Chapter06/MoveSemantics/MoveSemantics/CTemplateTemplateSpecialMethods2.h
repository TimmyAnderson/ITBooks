//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateTemplateSpecialMethods2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		template<typename TType>
		CTemplateTemplateSpecialMethods2(const TType& Value);
		CTemplateTemplateSpecialMethods2(const CTemplateTemplateSpecialMethods2&& Value) noexcept;
		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateTemplateSpecialMethods2(const volatile CTemplateTemplateSpecialMethods2&)=delete;
		virtual ~CTemplateTemplateSpecialMethods2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateTemplateSpecialMethods2::CTemplateTemplateSpecialMethods2(const TType& Value)
	: MValue()
{
	if constexpr (std::is_same<TType,CTemplateTemplateSpecialMethods2>::value)
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