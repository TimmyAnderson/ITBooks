//----------------------------------------------------------------------------------------------------------------------
#include "CIsNoThrowDefaultConstructible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowDefaultConstructible::CIsNoThrowDefaultConstructible(void) noexcept
	: MField1(100), MField2(111.222), MField3(100,222.333)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowDefaultConstructible::~CIsNoThrowDefaultConstructible(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsNoThrowDefaultConstructible::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsNoThrowDefaultConstructible::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CIsNoThrowDefaultConstructible::GetField3(void) const
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowDefaultConstructible::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowDefaultConstructible::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowDefaultConstructible::SetField3(const CNonTrivialType& Field3)
{
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowDefaultConstructible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------