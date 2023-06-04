//----------------------------------------------------------------------------------------------------------------------
#include "CValueWithConstructors.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors::CValueWithConstructors(void)
	: MValue(0)
{
	wcout << L"DEFAULT CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors::CValueWithConstructors(int Value)
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors::CValueWithConstructors(const CValueWithConstructors& Other)
	: MValue(Other.MValue)
{
	wcout << L"COPY CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors::CValueWithConstructors(CValueWithConstructors&& Other) noexcept
	: MValue(Other.MValue)
{
	wcout << L"MOVE CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors::~CValueWithConstructors(void)
{
	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors& CValueWithConstructors::operator=(const CValueWithConstructors& Other)
{
	MValue=Other.MValue;

	wcout << L"COPY OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CValueWithConstructors& CValueWithConstructors::operator=(CValueWithConstructors&& Other) noexcept
{
	MValue=Other.MValue;

	wcout << L"MOVE OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CValueWithConstructors::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------