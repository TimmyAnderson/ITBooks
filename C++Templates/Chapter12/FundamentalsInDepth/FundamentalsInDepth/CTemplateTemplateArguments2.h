//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE ma 1. TEMPLATE TYPE PARAMETER a 2. TEMPLATE TYPE PARAMETER s DEFAULT TEMPLATE TYPE ARGUMENT.
template<typename TType1, typename TType2=int>
class CTemplateTemplateArguments2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		std::wstring ToString(void) const;

	public:
		CTemplateTemplateArguments2(TType1 Field1, TType2 Field2);
		virtual ~CTemplateTemplateArguments2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateTemplateArguments2<TType1,TType2>::CTemplateTemplateArguments2(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateTemplateArguments2<TType1,TType2>::~CTemplateTemplateArguments2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
std::wstring CTemplateTemplateArguments2<TType1,TType2>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << "TEMPLATE TEMPLATE ARGUMENTS 2 - FIELD 1 [" << MField1 << L"]  FIELD 2 [" << MField2 << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------