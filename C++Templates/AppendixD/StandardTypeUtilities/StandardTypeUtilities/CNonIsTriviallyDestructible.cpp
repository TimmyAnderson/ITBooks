//----------------------------------------------------------------------------------------------------------------------
#include "CNonIsTriviallyDestructible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNonIsTriviallyDestructible::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CNonIsTriviallyDestructible::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CNonIsTriviallyDestructible::GetField3(void) const
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyDestructible::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyDestructible::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyDestructible::SetField3(const CNonTrivialType& Field3)
{
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyDestructible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------