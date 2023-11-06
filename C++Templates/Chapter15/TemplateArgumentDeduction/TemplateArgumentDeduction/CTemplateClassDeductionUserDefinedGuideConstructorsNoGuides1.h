//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFAULT VALUE pre TYPE PARAMETER [TType3] je TYPE [TType2].
template<typename TType1, typename TType2, typename TType3=TType2>
class CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;
		TType3													MValue3;

	public:
		CString Print(void) const;

	public:
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1(const TType1& Value1=TType1{}, const TType2& Value2=TType2{}, const TType3& Value3=TType3{});
		virtual ~CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1<TType1,TType2,TType3>::CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1(const TType1& Value1, const TType2& Value2, const TType3& Value3)
	: MValue1(Value1), MValue2(Value2), MValue3(Value3)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1<TType1,TType2,TType3>::~CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
CString CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1<TType1,TType2,TType3>::Print(void) const
{
	std::wstringstream											Stream;

	Stream << L"\tVALUE 1 - TYPE [" << GetTypeInfoName<decltype(MValue1)>() << L"] VALUE [" << MValue1 << L"]." << std::endl;
	Stream << L"\tVALUE 2 - TYPE [" << GetTypeInfoName<decltype(MValue2)>() << L"] VALUE [" << MValue2 << L"]." << std::endl;
	Stream << L"\tVALUE 3 - TYPE [" << GetTypeInfoName<decltype(MValue3)>() << L"] VALUE [" << MValue3 << L"]." << std::endl;

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------