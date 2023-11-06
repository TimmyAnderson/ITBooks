//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionImplicitGuide final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		CTemplateClassDeductionImplicitGuide(const TType1& Value1, const TType2& Value2);
		// !!! TEMPLATE CONSTRUCTOR.
		template<typename TLocalType>
		CTemplateClassDeductionImplicitGuide(const TType1& Value1, const TType2& Value2, const TLocalType& Value);
		virtual ~CTemplateClassDeductionImplicitGuide(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pre CONSTRUCTOR je generovany IMPLICIT DEDUCTION GUIDE.
template<typename TType1, typename TType2>
CTemplateClassDeductionImplicitGuide<TType1,TType2>::CTemplateClassDeductionImplicitGuide(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pre TEMPLATE CONSTRUCTOR je generovany IMPLICIT DEDUCTION GUIDE.
template<typename TType1, typename TType2>
template<typename TLocalType>
CTemplateClassDeductionImplicitGuide<TType1,TType2>::CTemplateClassDeductionImplicitGuide(const TType1& Value1, const TType2& Value2, const TLocalType& Value)
	: MValue1(Value1), MValue2(Value2)
{
	std::wcout << L"TEMPLATE CONSTRUCTOR - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionImplicitGuide<TType1,TType2>::~CTemplateClassDeductionImplicitGuide(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDeductionImplicitGuide<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDeductionImplicitGuide<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------