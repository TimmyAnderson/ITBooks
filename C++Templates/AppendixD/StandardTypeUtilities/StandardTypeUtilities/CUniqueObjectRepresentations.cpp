//----------------------------------------------------------------------------------------------------------------------
#include "CUniqueObjectRepresentations.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CUniqueObjectRepresentations::CUniqueObjectRepresentations(void)
	: MField1(0), MField2(0)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CUniqueObjectRepresentations::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
void CUniqueObjectRepresentations::SetField1(int Field1)
{
	MField1=Field1;
}
//----------------------------------------------------------------------------------------------------------------------
int CUniqueObjectRepresentations::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
void CUniqueObjectRepresentations::SetField2(int Field2)
{
	MField2=Field2;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CUniqueObjectRepresentations::SomeMethod(void)
{
	wcout << L"METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------