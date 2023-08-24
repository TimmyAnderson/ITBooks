//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE TEMPLATE PARAMETER ocakava TEMPLATE, ktora ma ako 1. TEMPLATE TYPE PARAMETER a ako 2. TEMPLATE NON-TYPE PARAMETER TYPE [int].
template<typename TType1, typename TType2, template<typename,int> typename TType3>
class CTemplateTemplateParameters2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;
		TType3<TType1,200>										MField3;

	public:
		std::wstring ToString(void) const;

	public:
		CTemplateTemplateParameters2(TType1 Field1, TType2 Field2, TType3<TType1,200> Field3);
		virtual ~CTemplateTemplateParameters2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,int> typename TType3>
CTemplateTemplateParameters2<TType1,TType2,TType3>::CTemplateTemplateParameters2(TType1 Field1, TType2 Field2, TType3<TType1,200> Field3)
	: MField1(Field1), MField2(Field2), MField3(Field3)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,int> typename TType3>
CTemplateTemplateParameters2<TType1,TType2,TType3>::~CTemplateTemplateParameters2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,int> typename TType3>
std::wstring CTemplateTemplateParameters2<TType1,TType2,TType3>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << "TEMPLATE TEMPLATE PARAMETERS 2 - FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"] FIELD 3 [" << MField3.ToString() << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------