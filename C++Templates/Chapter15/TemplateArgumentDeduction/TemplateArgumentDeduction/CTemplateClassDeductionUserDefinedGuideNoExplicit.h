//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionUserDefinedGuideNoExplicit final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void PrintTypes(void) const;

	public:
		CTemplateClassDeductionUserDefinedGuideNoExplicit(const TType1&);
		CTemplateClassDeductionUserDefinedGuideNoExplicit(TType1&&);
		virtual ~CTemplateClassDeductionUserDefinedGuideNoExplicit(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideNoExplicit<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideNoExplicit(const TType1&)
{
	std::wcout << L"CONSTRUCTOR [const TType&] CALLED. TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideNoExplicit<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideNoExplicit(TType1&&)
{
	std::wcout << L"CONSTRUCTOR [TType&&] CALLED. TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideNoExplicit<TType1,TType2>::~CTemplateClassDeductionUserDefinedGuideNoExplicit(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CTemplateClassDeductionUserDefinedGuideNoExplicit<TType1,TType2>::PrintTypes(void) const
{
	std::wcout << L"TYPES - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionUserDefinedGuideNoExplicit(const TType&) -> CTemplateClassDeductionUserDefinedGuideNoExplicit<TType,TType&>;
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionUserDefinedGuideNoExplicit(TType&&) -> CTemplateClassDeductionUserDefinedGuideNoExplicit<TType,TType>;
//----------------------------------------------------------------------------------------------------------------------