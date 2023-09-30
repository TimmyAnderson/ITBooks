//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE TEMPLATE PARAMETER ocakava TEMPLATE, ktora ma LUBOVOLNY POCET TEMPLATE TYPE PARAMETERS.
template<typename TType1, typename TType2, template<typename...> typename TType3>
class CTemplateTemplateParameters3 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;
		// !!!!!! FIELD ocakava TEMPLATE TEMPLATE AGRUMENT, ktory ma presne 2 TEMPLATE TYPE PARAMETERS.
		TType3<TType1,TType2>									MField3;

	public:
		std::wstring ToString(void) const;

	public:
		CTemplateTemplateParameters3(TType1 Field1, TType2 Field2, TType3<TType1,TType2> Field3);
		virtual ~CTemplateTemplateParameters3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename...> typename TType3>
CTemplateTemplateParameters3<TType1,TType2,TType3>::CTemplateTemplateParameters3(TType1 Field1, TType2 Field2, TType3<TType1,TType2> Field3)
	: MField1(Field1), MField2(Field2), MField3(Field3)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename...> typename TType3>
CTemplateTemplateParameters3<TType1,TType2,TType3>::~CTemplateTemplateParameters3(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename...> typename TType3>
std::wstring CTemplateTemplateParameters3<TType1,TType2,TType3>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << L"TEMPLATE TEMPLATE PARAMETERS 3 - FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"] FIELD 3 [" << MField3.ToString() << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------