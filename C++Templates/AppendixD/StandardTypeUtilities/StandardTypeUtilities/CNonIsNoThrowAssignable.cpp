//----------------------------------------------------------------------------------------------------------------------
#include "CNonIsNoThrowAssignable.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNonIsNoThrowAssignable::CNonIsNoThrowAssignable(int Value1, double Value2)
	: MField(Value1,Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CNonIsNoThrowAssignable::~CNonIsNoThrowAssignable(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNonIsNoThrowAssignable& CNonIsNoThrowAssignable::operator=(const CNonTrivialType& Other)
{
	MField.SetField1(Other.GetField1());
	MField.SetField2(Other.GetField2());

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CNonIsNoThrowAssignable::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsNoThrowAssignable::SetField(const CNonTrivialType& Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonIsNoThrowAssignable::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------