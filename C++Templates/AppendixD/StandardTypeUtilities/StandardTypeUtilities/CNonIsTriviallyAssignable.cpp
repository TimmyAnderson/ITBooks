//----------------------------------------------------------------------------------------------------------------------
#include "CNonIsTriviallyAssignable.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNonIsTriviallyAssignable::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyAssignable::SetField(int Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonIsTriviallyAssignable::SomeMethod(void)
{
	wcout << "METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------