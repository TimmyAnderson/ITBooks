//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CTemplateClassDeductionOverloadedConstructorsInner.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateClassDeductionOverloadedConstructorsOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CTemplateClassDeductionOverloadedConstructorsOuter(const CTemplateClassDeductionOverloadedConstructorsInner<TType>& Value);
		CTemplateClassDeductionOverloadedConstructorsOuter(CTemplateClassDeductionOverloadedConstructorsInner<TType>&& Value);
		virtual ~CTemplateClassDeductionOverloadedConstructorsOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionOverloadedConstructorsOuter<TType>::CTemplateClassDeductionOverloadedConstructorsOuter(const CTemplateClassDeductionOverloadedConstructorsInner<TType>& Value)
	: MValue(Value.GetValue())
{
	std::wcout << L"CONSTRUCTOR [const TType&] CALLED. TYPE [" << GetTypeInfoName<TType>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionOverloadedConstructorsOuter<TType>::CTemplateClassDeductionOverloadedConstructorsOuter(CTemplateClassDeductionOverloadedConstructorsInner<TType>&& Value)
	: MValue(Value.GetValue())
{
	std::wcout << L"CONSTRUCTOR [TType&&] CALLED. TYPE [" << GetTypeInfoName<TType>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionOverloadedConstructorsOuter<TType>::~CTemplateClassDeductionOverloadedConstructorsOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateClassDeductionOverloadedConstructorsOuter<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename TType>
CTemplateClassDeductionOverloadedConstructorsOuter(CTemplateClassDeductionOverloadedConstructorsInner<TType>) -> CTemplateClassDeductionOverloadedConstructorsOuter<TType>;
//----------------------------------------------------------------------------------------------------------------------