//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateClassDeductionInjectedClassNames final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		template<typename TLocalType>
		void TestInjectedName(TLocalType Value) const;

	public:
		template<typename TLocalType>
		CTemplateClassDeductionInjectedClassNames(TLocalType Value);
		virtual ~CTemplateClassDeductionInjectedClassNames(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TLocalType>
CTemplateClassDeductionInjectedClassNames<TType>::CTemplateClassDeductionInjectedClassNames(TLocalType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateClassDeductionInjectedClassNames<TType>::~CTemplateClassDeductionInjectedClassNames(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateClassDeductionInjectedClassNames<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TLocalType>
void CTemplateClassDeductionInjectedClassNames<TType>::TestInjectedName(TLocalType Value) const
{
	std::wcout << L"PARAMETER - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;

	// !!!!! Aj napriek tomu, VARIABLE [Value] ma TYPE [double], tak DEDUCED TYPE je TYPE [CTemplateClassDeductionInjectedClassNames<int>]. Je to preto, lebo TYPE [CTemplateClassDeductionInjectedClassNames] je INJECTED CLASS NAME.
	CTemplateClassDeductionInjectedClassNames					Object(Value);

	std::wcout << L"TEST - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------