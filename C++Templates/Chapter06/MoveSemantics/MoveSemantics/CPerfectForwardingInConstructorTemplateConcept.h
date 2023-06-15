//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptConvertibleToWString=std::is_convertible<TType,std::wstring>::value;
//----------------------------------------------------------------------------------------------------------------------
class CPerfectForwardingInConstructorTemplateConcept final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		// !!!!! PERFECT FORWARDING CONSTRUCTOR.
		// !!!!! Ak CONCEPT nie je splneny, tak CONSTRUCTOR je VYRADENY z CANDIDATE SET a posudzovane su dalsie FUNCTIONS.
		template<typename TType>
		requires ConceptConvertibleToWString<TType>
		explicit CPerfectForwardingInConstructorTemplateConcept(TType&& Value);
		CPerfectForwardingInConstructorTemplateConcept(const CPerfectForwardingInConstructorTemplateConcept& Value);
		CPerfectForwardingInConstructorTemplateConcept(CPerfectForwardingInConstructorTemplateConcept&& Value) noexcept;
		virtual ~CPerfectForwardingInConstructorTemplateConcept(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PERFECT FORWARDING CONSTRUCTOR.
// !!!!! Ak CONCEPT nie je splneny, tak CONSTRUCTOR je VYRADENY z CANDIDATE SET a posudzovane su dalsie FUNCTIONS.
template<typename TType>
requires ConceptConvertibleToWString<TType>
CPerfectForwardingInConstructorTemplateConcept::CPerfectForwardingInConstructorTemplateConcept(TType&& Value)
	: MValue(std::forward<TType>(Value))
{
	std::wcout << L"TEMPLATE - FORWARDING CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------