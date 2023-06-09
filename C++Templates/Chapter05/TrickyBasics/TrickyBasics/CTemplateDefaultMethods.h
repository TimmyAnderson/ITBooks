//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateDefaultMethods final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:	
		// !!! CONVERSION OPERATOR, ktory ma zaroven vlastny TEMPLATE PARAMETER, nezavisly na TEMPLATE PARAMETER TEMPLATE CLASS.
		template<typename TOtherType>
		CTemplateDefaultMethods<TType>& operator=(const CTemplateDefaultMethods<TOtherType>& Other);

	public:
		const TType& Get(void) const noexcept;

	public:	
		CTemplateDefaultMethods(const TType& Value);
		virtual ~CTemplateDefaultMethods(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateDefaultMethods<TType>::CTemplateDefaultMethods(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateDefaultMethods<TType>::~CTemplateDefaultMethods(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETERS TEMPLATE CLASS.
template<typename TType>
// !!! TEMPLATE PARAMETERS TEMPLATE METHOD (OPERATOR).
template<typename TOtherType>
CTemplateDefaultMethods<TType>& CTemplateDefaultMethods<TType>::operator=(const CTemplateDefaultMethods<TOtherType>& Other)
{
	std::wcout << L"USER DEFINED OPERATOR [OPERATOR=] CALLED !" << std::endl;

	const TOtherType&											OriginalValue=Other.Get();
	TType														ConvertedValue=static_cast<TType>(OriginalValue);

	MValue=ConvertedValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateDefaultMethods<TType>::Get(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------