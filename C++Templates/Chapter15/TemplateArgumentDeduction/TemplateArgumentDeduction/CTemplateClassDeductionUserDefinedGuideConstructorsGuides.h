//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionUserDefinedGuideConstructorsGuides final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateClassDeductionUserDefinedGuideConstructorsGuides(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideConstructorsGuides<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideConstructorsGuides(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideConstructorsGuides<TType1,TType2>::~CTemplateClassDeductionUserDefinedGuideConstructorsGuides(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDeductionUserDefinedGuideConstructorsGuides<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDeductionUserDefinedGuideConstructorsGuides<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionUserDefinedGuideConstructorsGuides(const wchar_t*,TType) -> CTemplateClassDeductionUserDefinedGuideConstructorsGuides<CString,TType>;
//----------------------------------------------------------------------------------------------------------------------