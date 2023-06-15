//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
class CTemplateTemplateSpecialMethods3 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CTemplateTemplateSpecialMethods3(const std::wstring& Value);
		template<typename TType,typename=std::enable_if<std::is_same<TType,CTemplateTemplateSpecialMethods3>::value>::type>
		CTemplateTemplateSpecialMethods3(const TType& Value);
		// !!!!! Vdaka pouzitiu DELETE COPY CONSTRUCTOR, ktory ma aplikovany aj KEYWORD [volatile] je mozne prinutit C++, aby volal pri COPY SEMANTICS TEMPLATE CONSTRUCTOR.
		CTemplateTemplateSpecialMethods3(const volatile CTemplateTemplateSpecialMethods3&)=delete;
		virtual ~CTemplateTemplateSpecialMethods3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType,typename>
CTemplateTemplateSpecialMethods3::CTemplateTemplateSpecialMethods3(const TType& Value)
	: MValue(Value.GetValue())
{
	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------