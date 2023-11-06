//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct STemplateClassDeductionImplicitGuideSupressionValue
{
//----------------------------------------------------------------------------------------------------------------------
	using														Type=TType;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionImplicitGuideSupression final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		// !!!!! Pouzitie USING, ktory refereruje na iny TYPE sposobi, ze IMPLICIT DEDUCTION GUIDE NEBUDE GENEROVANY. Je to dosledok toho, ze TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type] a TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type] NIE SU DEDUCTION CONTEXTS.
		CTemplateClassDeductionImplicitGuideSupression(const typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type& Value1, const typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type& Value2);
		virtual ~CTemplateClassDeductionImplicitGuideSupression(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pre CONSTRUCTOR je generovany IMPLICIT DEDUCTION GUIDE.
// !!!!! Pouzitie USING, ktory refereruje na iny TYPE vsak sposobi, ze IMPLICIT DEDUCTION GUIDE NEBUDE GENEROVANY. Je to dosledok toho, ze TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type] a TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type] NIE SU DEDUCTION CONTEXTS.
template<typename TType1, typename TType2>
CTemplateClassDeductionImplicitGuideSupression<TType1,TType2>::CTemplateClassDeductionImplicitGuideSupression(const typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type& Value1, const typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionImplicitGuideSupression<TType1,TType2>::~CTemplateClassDeductionImplicitGuideSupression(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDeductionImplicitGuideSupression<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDeductionImplicitGuideSupression<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------