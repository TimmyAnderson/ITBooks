//----------------------------------------------------------------------------------------------------------------------
#include "CValue.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValue::CValue(int Value)
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValue::~CValue(void) noexcept
{
	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CValue::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------