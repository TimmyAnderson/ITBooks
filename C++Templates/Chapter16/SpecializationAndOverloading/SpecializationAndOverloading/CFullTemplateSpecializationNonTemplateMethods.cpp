//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationNonTemplateMethods.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION.
template<>
void CFullTemplateSpecializationNonTemplateMethods<double>::Print2(void) const
{
	wcout << L"TEMPLATE SPECIALIZATION METHOD 2 <double> - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION.
template<>
void CFullTemplateSpecializationNonTemplateMethods<double>::Print3(double Parameter) const
{
	wcout << L"TEMPLATE SPECIALIZATION METHOD 3 <double> - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------