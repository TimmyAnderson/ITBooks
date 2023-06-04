//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <wchar.h>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateArgumentsDeductionByReference
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& Get1(void) const noexcept;
		const TType2& Get2(void) const noexcept;

	public:
		CTemplateArgumentsDeductionByReference(void)
			: MValue1(), MValue2()
		{
		}

		// !!! CONSTRUCTOR PARAMETERS sa prenasaju BY-REFERENCE, kedy sa NEROBI TYPE DECAY.
		CTemplateArgumentsDeductionByReference(const TType1& Value1, const TType2& Value2)
			: MValue1(), MValue2()
		{
#ifdef _MSC_VER
			// !!!!! Kedze TYPE 'TType1' je ARRAY 'wchar_t', NIE JE mozne priradit ARRAY do ARRAY, ale je potrebne vykonat kopiu ARRAY ITEMS.
			wcscpy_s(MValue1,sizeof(MValue1)/sizeof(MValue1[0]),Value1);
			MValue2=Value2;
#else
			wcscpy(MValue1,Value1);
			MValue2=Value2;
#endif
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateArgumentsDeductionByReference<TType1,TType2>::Get1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateArgumentsDeductionByReference<TType1,TType2>::Get2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------