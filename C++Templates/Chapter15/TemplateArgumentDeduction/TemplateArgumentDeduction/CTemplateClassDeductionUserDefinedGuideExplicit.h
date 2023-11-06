//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDeductionUserDefinedGuideExplicit final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void PrintTypes(void) const;

	public:
		CTemplateClassDeductionUserDefinedGuideExplicit(const TType1&);
		CTemplateClassDeductionUserDefinedGuideExplicit(TType1&&);
		virtual ~CTemplateClassDeductionUserDefinedGuideExplicit(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideExplicit<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideExplicit(const TType1&)
{
	std::wcout << L"CONSTRUCTOR [const TType&] CALLED. TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideExplicit<TType1,TType2>::CTemplateClassDeductionUserDefinedGuideExplicit(TType1&&)
{
	std::wcout << L"CONSTRUCTOR [TType&&] CALLED. TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDeductionUserDefinedGuideExplicit<TType1,TType2>::~CTemplateClassDeductionUserDefinedGuideExplicit(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CTemplateClassDeductionUserDefinedGuideExplicit<TType1,TType2>::PrintTypes(void) const
{
	std::wcout << L"TYPES - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionUserDefinedGuideExplicit(const TType&) -> CTemplateClassDeductionUserDefinedGuideExplicit<TType,TType&>;
//----------------------------------------------------------------------------------------------------------------------
// !!! EXPLICIT DEDUCTION GUIDE.
template<typename TType>
explicit CTemplateClassDeductionUserDefinedGuideExplicit(TType&&) -> CTemplateClassDeductionUserDefinedGuideExplicit<TType,TType>;
//----------------------------------------------------------------------------------------------------------------------