//----------------------------------------------------------------------------------------------------------------------
#include "CIsMoveConstructible1.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 26439 )
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsMoveConstructible1::CIsMoveConstructible1(int Field1, double Field2)
	: MField1(Field1), MField2(Field2), MField3(100,222.333)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsMoveConstructible1::CIsMoveConstructible1(CIsMoveConstructible1&& Other)
	: MField1(move(Other.MField1)), MField2(move(Other.MField2)), MField3(move(Other.MField3.GetField1()),move(Other.MField3.GetField2()))
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsMoveConstructible1::~CIsMoveConstructible1(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsMoveConstructible1::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
double CIsMoveConstructible1::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
const CNonTrivialType& CIsMoveConstructible1::GetField3(void) const
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsMoveConstructible1::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsMoveConstructible1::SetField2(double Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
void CIsMoveConstructible1::SetField3(const CNonTrivialType& Field3)
{
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsMoveConstructible1::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------