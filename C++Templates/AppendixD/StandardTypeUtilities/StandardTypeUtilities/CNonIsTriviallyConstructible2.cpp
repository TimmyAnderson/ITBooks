//----------------------------------------------------------------------------------------------------------------------
#include "CNonIsTriviallyConstructible2.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNonIsTriviallyConstructible2::CNonIsTriviallyConstructible2(void)
	: MField1(0), MField2(0.0)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNonIsTriviallyConstructible2::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CNonIsTriviallyConstructible2::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyConstructible2::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyConstructible2::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyConstructible2::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------