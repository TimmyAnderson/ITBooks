//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <iostream>
#include <concepts> 
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptTemplateClassMethodConcept=requires(TType A, TType B)
{
	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{A.GetValue()} -> std::convertible_to<std::wstring>;

	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{B.GetValue()} -> std::convertible_to<std::wstring>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateClassMethodWithConcept final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue1;
		TType													MValue2;

	public:
		const TType& GetValue1(void) const noexcept;
		const TType& GetValue2(void) const noexcept;

	public:
		std::wstring Print(void) const requires ConceptTemplateClassMethodConcept<TType>;

	public:
		CTemplateClassMethodWithConcept(const TType& Value1, const TType& Value2);
		virtual ~CTemplateClassMethodWithConcept(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassMethodWithConcept<TType>::CTemplateClassMethodWithConcept(const TType& Value1, const TType& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassMethodWithConcept<TType>::~CTemplateClassMethodWithConcept(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateClassMethodWithConcept<TType>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateClassMethodWithConcept<TType>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENT je aplikovany IBA na TEMPLATE CLASS METHOD.
template<typename TType>
std::wstring CTemplateClassMethodWithConcept<TType>::Print(void) const requires ConceptTemplateClassMethodConcept<TType>
{
	std::wstringstream											Stream;

	// !!!!! CODE vyzaduje, aby TYPE 'TType' mal METHOD [const wstring& GetValue(void) const].
	Stream << L"VALUE 1 [" << MValue1.GetValue() << L"]" << L" VALUE 2 [" << MValue2.GetValue() << L"]";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------