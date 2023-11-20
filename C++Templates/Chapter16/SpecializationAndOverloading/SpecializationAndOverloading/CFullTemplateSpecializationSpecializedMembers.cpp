//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationSpecializedMembers.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE VARIABLE SPECIALIZATION DEFINITION.
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION MUSI mat aplikovanu SYNTAX [template<>].
template<>
double											CFullTemplateSpecializationSpecializedMembers<double>::MMyStaticField=123.456;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION DEFINITION.
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION MUSI mat aplikovanu SYNTAX [template<>].
template<>
void CFullTemplateSpecializationSpecializedMembers<double>::MyMethod(double Parameter) const
{
	wcout << L"TEMPLATE SPECIALIZATION METHOD <double> - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! STATIC FIELD INNER TEMPLATE CLASS SPECIALIZATION.
// !!!!! STATIC FIELD INNER TEMPLATE CLASS SPECIALIZATION MUSI mat aplikovanu SYNTAX [template<>].
template<>
template<>
double															CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>::MMyInnerStaticField=456.789;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFINITION NON-TEMPLATE INNER CLASS METHOD SPECIALIZATION.
// !!!!! NON-TEMPLATE INNER CLASS METHOD SPECIALIZATION MUSI mat aplikovanu SYNTAX [template<>].
template<>
template<>
void CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>::MyInnerMethod(double Parameter) const
{
	wcout << L"TEMPLATE SPECIALIZATION INNER CLASS METHOD <short>::<double> - TYPE [" << GetTypeInfoName<double>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION STATIC FIELD.
// !!!!! TEMPLATE CLASS SPECIALIZATION STATIC FIELD NESMIE mat aplikovanu SYNTAX [template<>].
//template<>
long											CFullTemplateSpecializationSpecializedMembers<long>::MMyStaticField=12345;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION METHOD.
// !!!!! TEMPLATE CLASS SPECIALIZATION NESMIE mat aplikovanu SYNTAX [template<>].
//template<>
void CFullTemplateSpecializationSpecializedMembers<long>::MyMethod(long Parameter) const
{
	wcout << L"TEMPLATE CLASS SPECIALIZATION METHOD <long> - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------