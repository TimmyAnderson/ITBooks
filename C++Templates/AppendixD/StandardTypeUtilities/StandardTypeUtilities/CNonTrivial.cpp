//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivial.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNonTrivial::CNonTrivial(void)
	: MField(0)
{
}
//----------------------------------------------------------------------------------------------------------------------
CNonTrivial::~CNonTrivial(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNonTrivial::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonTrivial::SetField(int Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonTrivial::SomeMethod(void)
{
	wcout << "METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------