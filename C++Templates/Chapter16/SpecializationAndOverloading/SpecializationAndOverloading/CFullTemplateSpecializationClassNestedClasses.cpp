//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationClassNestedClasses.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFullTemplateSpecializationClassNestedClassesOuter<bool>::CFullTemplateSpecializationClassNestedClassesInner<double>::Print(double Parameter) const
{
	wcout << L"OUTER TEMPLATE CLASS SPECIALIZATION <bool> INNER TEMPLATE CLASS SPECIALIZATION <double> METHOD - OUTER TYPE [" << GetTypeInfoName<bool>() << L"] INNER TYPE [" << GetTypeInfoName<double>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFullTemplateSpecializationClassNestedClassesOuter<long>::CFullTemplateSpecializationClassNestedClassesInner<short>::Print(short Parameter) const
{
	wcout << L"OUTER TEMPLATE CLASS SPECIALIZATION <long> INNER TEMPLATE CLASS SPECIALIZATION <short> METHOD - OUTER TYPE [" << GetTypeInfoName<long>() << L"] INNER TYPE [" << GetTypeInfoName<short>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------