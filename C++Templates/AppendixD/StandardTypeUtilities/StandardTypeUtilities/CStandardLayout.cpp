//----------------------------------------------------------------------------------------------------------------------
#include "CStandardLayout.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CStandardLayout::CStandardLayout(void)
	: MField(0)
{
}
//----------------------------------------------------------------------------------------------------------------------
CStandardLayout::~CStandardLayout(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CStandardLayout::GetField(void) const
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
void CStandardLayout::SetField(int Field)
{
	MField=Field;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CStandardLayout::SomeMethod(void)
{
	wcout << "METHOD [void SomeMethod(void)] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------