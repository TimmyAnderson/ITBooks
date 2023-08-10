//----------------------------------------------------------------------------------------------------------------------
#include "CIsTriviallyMoveAssignable.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsTriviallyMoveAssignable::CIsTriviallyMoveAssignable(int Field1, double Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsTriviallyMoveAssignable::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsTriviallyMoveAssignable::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyMoveAssignable::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyMoveAssignable::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsTriviallyMoveAssignable::SomeMethod(void)
{
	wcout << "METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------