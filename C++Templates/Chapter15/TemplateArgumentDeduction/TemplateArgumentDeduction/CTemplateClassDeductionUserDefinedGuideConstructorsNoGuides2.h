//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2<TType1,TType2>::~CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------