//----------------------------------------------------------------------------------------------------------------------
#include "CIsAssignable.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsAssignable::CIsAssignable(int Value1, double Value2)
	: MField(Value1,Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsAssignable::~CIsAssignable(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsAssignable& CIsAssignable::operator=(const CNonTrivialType& Other)
{
	MField.SetField1(Other.GetField1());
	MField.SetField2(Other.GetField2());

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CIsAssignable::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsAssignable::SetField(const CNonTrivialType& Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsAssignable::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------