//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE DECLARATION.
template<typename TType>
class CAutomaticInstantiation1;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DECLARATION je postacujuca na definovanie POINTER VARIABLE.
CAutomaticInstantiation1<int>*									AutomaticInstantiation1Pointer=nullptr;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE DECLARATION NIE je postacujuca na definovanie VALUE VARIABLE.
//CAutomaticInstantiation1<int>									AutomaticInstantiation1Value(100);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE DEFINITION.
template<typename TType>
class CAutomaticInstantiation1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CAutomaticInstantiation1(TType Value);
		virtual ~CAutomaticInstantiation1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestAutomaticInstantiation1(const CAutomaticInstantiation1<int>& Parameter)
{
	// !!!!! COMPILER staci DECLARATION TEMPLATE METHOD.
	std::wcout << L"VALUE [" << Parameter.GetValue() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CONSTRUCTOR DEFINITION.
template<typename TType>
CAutomaticInstantiation1<TType>::CAutomaticInstantiation1(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE DESTRUCTOR DEFINITION.
template<typename TType>
CAutomaticInstantiation1<TType>::~CAutomaticInstantiation1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE METHOD DEFINITION.
template<typename TType>
const TType& CAutomaticInstantiation1<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------