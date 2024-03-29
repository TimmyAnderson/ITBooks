//----------------------------------------------------------------------------------------------------------------------
#include "CIsNoThrowCopyConstructible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowCopyConstructible::CIsNoThrowCopyConstructible(int Field1, double Field2)
	: MField1(Field1), MField2(Field2), MField3(100,222.333)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowCopyConstructible::CIsNoThrowCopyConstructible(const CIsNoThrowCopyConstructible& Other) noexcept
	: MField1(Other.MField1), MField2(Other.MField2), MField3(Other.MField3.GetField1(),Other.MField3.GetField2())
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsNoThrowCopyConstructible::~CIsNoThrowCopyConstructible(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsNoThrowCopyConstructible::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsNoThrowCopyConstructible::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CIsNoThrowCopyConstructible::GetField3(void) const
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowCopyConstructible::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowCopyConstructible::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowCopyConstructible::SetField3(const CNonTrivialType& Field3)
{
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsNoThrowCopyConstructible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------