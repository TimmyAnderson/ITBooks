//----------------------------------------------------------------------------------------------------------------------
#include "CIsNoThrowConstructible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowConstructible::CIsNoThrowConstructible(int Field1)
	: MField1(Field1), MField2(111.222), MField3(100,222.333)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowConstructible::CIsNoThrowConstructible(int Field1, double Field2) noexcept
	: MField1(Field1), MField2(Field2), MField3(100,222.333)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowConstructible::~CIsNoThrowConstructible(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsNoThrowConstructible::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsNoThrowConstructible::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CIsNoThrowConstructible::GetField3(void) const
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowConstructible::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowConstructible::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowConstructible::SetField3(const CNonTrivialType& Field3)
{
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowConstructible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------