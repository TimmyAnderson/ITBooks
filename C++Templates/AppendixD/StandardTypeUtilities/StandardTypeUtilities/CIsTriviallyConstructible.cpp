//----------------------------------------------------------------------------------------------------------------------
#include "CIsTriviallyConstructible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsTriviallyConstructible::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsTriviallyConstructible::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyConstructible::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyConstructible::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyConstructible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------