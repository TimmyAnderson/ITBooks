//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateMethodsSpecializations final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void NonTemplateMethod(TType Value);

	public:
		template<class TMethodType>
		void TemplateMethod(TType Value1, TMethodType Value2);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateMethodsSpecializations<TType>::NonTemplateMethod(TType Value)
{
	std::wcout << L"111 - TEMPLATE METHOD [void NonTemplateMethod(void)] is CALLED ! VALUE [" << Value << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<class TMethodType>
void CTemplateMethodsSpecializations<TType>::TemplateMethod(TType Value1, TMethodType Value2)
{
	std::wcout << L"222 - TEMPLATE METHOD [void TemplateMethod(TType Value1, TMethodType Value2)] is CALLED ! VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE METHOD pre TEMPLATE CLASS SPECIALIZATION.
template<>
void CTemplateMethodsSpecializations<double>::NonTemplateMethod(double Value)
{
	std::wcout << L"333 - TEMPLATE CLASS SPECIALIZATION METHOD [void NonTemplateMethod(void)] is CALLED ! VALUE [" << Value << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE METHOD pre TEMPLATE CLASS SPECIALIZATION.
template<>
template<class TMethodType>
void CTemplateMethodsSpecializations<double>::TemplateMethod(double Value1, TMethodType Value2)
{
	std::wcout << L"444 - TEMPLATE CLASS SPECIALIZATION METHOD [void TemplateMethod(double Value1, TMethodType Value2)] is CALLED ! VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE METHOD SPECIALIZATION pre TEMPLATE CLASS SPECIALIZATION.
template<>
template<>
void CTemplateMethodsSpecializations<double>::TemplateMethod<long>(double Value1, long Value2)
{
	std::wcout << L"555 - TEMPLATE CLASS SPECIALIZATION METHOD SPECIALIZATION [void TemplateMethod<long>(double Value1, long Value2)] is CALLED ! VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR.
// !!!!! Pre TEMPLATE CLASSES, NIE JE mozne definovat TEMPLATE METHOD SPECIALIZATIONS. IBA pre TEMPLATE CLASSES SPECIALIZATIONS je mozne definovat TEMPLATE METHOD SPECIALIZATIONS.
template<typename TType>
template<>
void CTemplateMethodsSpecializations<TType>::TemplateMethod<long double>(TType Value1, long double Value2)
{
	std::wcout << L"666 - TEMPLATE CLASS METHOD SPECIALIZATION [void TemplateMethod<long double>(TType Value1, long double Value2)] is CALLED ! VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << std::endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------