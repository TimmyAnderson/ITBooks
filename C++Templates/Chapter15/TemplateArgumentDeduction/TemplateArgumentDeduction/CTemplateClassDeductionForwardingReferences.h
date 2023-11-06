//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateClassDeductionForwardingReferences final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CTemplateClassDeductionForwardingReferences(const TType& Value);
		// !!! Pouziva sa FORWARDING REFERENCE.
		CTemplateClassDeductionForwardingReferences(TType&& Value);
		virtual ~CTemplateClassDeductionForwardingReferences(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionForwardingReferences<TType>::CTemplateClassDeductionForwardingReferences(const TType& Value)
	: MValue(Value)
{
	std::wcout << L"CONSTRUCTOR [const TType&] CALLED. TYPE 1 [" << GetTypeInfoName<TType>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Pouziva sa FORWARDING REFERENCE.
template<typename TType>
CTemplateClassDeductionForwardingReferences<TType>::CTemplateClassDeductionForwardingReferences(TType&& Value)
	: MValue(Value)
{
	std::wcout << L"CONSTRUCTOR [TType&&] CALLED. TYPE 1 [" << GetTypeInfoName<TType>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionForwardingReferences<TType>::~CTemplateClassDeductionForwardingReferences(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateClassDeductionForwardingReferences<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------