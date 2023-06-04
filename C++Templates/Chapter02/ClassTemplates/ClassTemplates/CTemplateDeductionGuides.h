//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateDeductionGuides
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		TType1 Get1(void) const noexcept;
		TType2 Get2(void) const noexcept;

	public:
		CTemplateDeductionGuides(void)
			: MValue1(), MValue2()
		{
		}

		// !!! CONSTRUCTOR PARAMETERS sa prenasaju BY-VALUE, kedy sa robi TYPE DECAY.
		CTemplateDeductionGuides(TType1 Value1, TType2 Value2)
			: MValue1(Value1), MValue2(Value2)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 CTemplateDeductionGuides<TType1,TType2>::Get1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 CTemplateDeductionGuides<TType1,TType2>::Get2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEDUCTION GUIDE, ktory mapuje PARAMETETERS tu definovaneho PSEUDO CONSTRUCTOR na TEMPLATE ARGUMENTS TEMPLATE CLASS.
// !!!!! Pre PSEUDO CONSTRUCTOR, ktory ma TYPE [const wchar_t*] a TYPE [const wchar_t*] sa vytvori CLASS [CTemplateDeductionGuides<wstring,wstring>].
CTemplateDeductionGuides(const wchar_t* Value1, const wchar_t* Value2) -> CTemplateDeductionGuides<std::wstring,std::wstring>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DEDUCTION GUIDE, ktory mapuje PARAMETETERS tu definovaneho PSEUDO CONSTRUCTOR na TEMPLATE ARGUMENTS TEMPLATE CLASS.
// !!!!! Pre PSEUDO CONSTRUCTOR, ktory ma TYPE [const wchar_t*] a TYPE [TType] sa vytvori CLASS [CTemplateDeductionGuides<wstring,TType>].
template <typename TType>
CTemplateDeductionGuides(const wchar_t* Value1, TType Value2) -> CTemplateDeductionGuides<std::wstring,TType>;
//----------------------------------------------------------------------------------------------------------------------