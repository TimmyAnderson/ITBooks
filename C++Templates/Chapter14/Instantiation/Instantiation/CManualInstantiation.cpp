//----------------------------------------------------------------------------------------------------------------------
#include "CManualInstantiation.h"
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TRANSLATION UNIT ako JEDINY obsahuje DEFINITIONS TEMPLATE METHODS.
template<typename TType>
CManualInstantiation<TType>::CManualInstantiation(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CManualInstantiation<TType>::~CManualInstantiation(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CManualInstantiation<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TRANSLATION UNIT ako JEDINY obsahuje DEFINITION TEMPLATE FUNCTION.
template<typename TType>
void ManualInstantiationFunction(const TType& Value)
{
	wcout << L"FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() <<"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze ine TRANSLATION UNITS NEMAJU DEFINITIONS TEMPLATE METHODS, a teda C++ NEMOZE vygenerovat BINARY CODE pre tieto METHODS, je ich nutne vygenerovat v tomto TRANSLATION UNIT pomocou EXPLICIT INSTANTIATION, inak hodi LINKER ERROR.
template class CManualInstantiation<int>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze ine TRANSLATION UNITS NEMAJU DEFINITION TEMPLATE FUNCTION, a teda C++ NEMOZE vygenerovat BINARY CODE pre tuto FUNCTION, je ju nutne vygenerovat v tomto TRANSLATION UNIT pomocou EXPLICIT INSTANTIATION, inak hodi LINKER ERROR.
template void ManualInstantiationFunction<int>(const int&);
//----------------------------------------------------------------------------------------------------------------------