//----------------------------------------------------------------------------------------------------------------------
#include "CIsConvertible.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CIsConvertible::CIsConvertible(int Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CIsConvertible::~CIsConvertible(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CIsConvertible::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CIsConvertible::SetField(int Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CIsConvertible::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------