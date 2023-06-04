//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <iostream>
#include <concepts> 
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptTemplateClassConcept=requires(TType A, TType B)
{
	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{A.GetValue()} -> std::convertible_to<std::wstring>;

	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{B.GetValue()} -> std::convertible_to<std::wstring>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptTemplateClassConcept<TType>
class CTemplateClassWithConcept final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue1;
		TType													MValue2;

	public:
		const TType& GetValue1(void) const noexcept;
		const TType& GetValue2(void) const noexcept;

	public:
		std::wstring Print(void) const;

	public:
		CTemplateClassWithConcept(const TType& Value1, const TType& Value2);
		virtual ~CTemplateClassWithConcept(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENTS aplikovane na CLASS MUSIA byt aplikovane aj na CLASS METHODS.
template<typename TType> requires ConceptTemplateClassConcept<TType>
CTemplateClassWithConcept<TType>::CTemplateClassWithConcept(const TType& Value1, const TType& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENTS aplikovane na CLASS MUSIA byt aplikovane aj na CLASS METHODS.
template<typename TType> requires ConceptTemplateClassConcept<TType>
CTemplateClassWithConcept<TType>::~CTemplateClassWithConcept(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENTS aplikovane na CLASS MUSIA byt aplikovane aj na CLASS METHODS.
template<typename TType> requires ConceptTemplateClassConcept<TType>
const TType& CTemplateClassWithConcept<TType>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENTS aplikovane na CLASS MUSIA byt aplikovane aj na CLASS METHODS.
template<typename TType> requires ConceptTemplateClassConcept<TType>
const TType& CTemplateClassWithConcept<TType>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENTS aplikovane na CLASS MUSIA byt aplikovane aj na CLASS METHODS.
template<typename TType> requires ConceptTemplateClassConcept<TType>
std::wstring CTemplateClassWithConcept<TType>::Print(void) const
{
	std::wstringstream											Stream;

	// !!!!! CODE vyzaduje, aby TYPE 'TType' mal METHOD [const wstring& GetValue(void) const].
	Stream << L"VALUE 1 [" << MValue1.GetValue() << L"]" << L" VALUE 2 [" << MValue2.GetValue() << L"]";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------