//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEDUCTION GUIDE.
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides(TType1,TType2) -> CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides<TType1,TType2>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides(const wchar_t*,TType) -> CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides<CString,TType>;
//----------------------------------------------------------------------------------------------------------------------