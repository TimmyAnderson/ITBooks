//----------------------------------------------------------------------------------------------------------------------
#include "CNonTriviallyCopyable.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNonTriviallyCopyable::CNonTriviallyCopyable(void)
	: MField(0)
{
}
//----------------------------------------------------------------------------------------------------------------------
CNonTriviallyCopyable::~CNonTriviallyCopyable(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNonTriviallyCopyable::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CNonTriviallyCopyable::SetField(int Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CNonTriviallyCopyable::SomeMethod(void)
{
	wcout << "METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------