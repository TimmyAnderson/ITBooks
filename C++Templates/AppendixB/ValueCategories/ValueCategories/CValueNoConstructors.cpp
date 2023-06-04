//----------------------------------------------------------------------------------------------------------------------
#include "CValueNoConstructors.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
CValueNoConstructors::CValueNoConstructors(void)
	: MValue(0)
{
	wcout << L"DEFAULT CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueNoConstructors::CValueNoConstructors(int Value)
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueNoConstructors::~CValueNoConstructors(void)
{
	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CValueNoConstructors::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------