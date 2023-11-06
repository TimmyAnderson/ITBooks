//----------------------------------------------------------------------------------------------------------------------
#include "CValue2.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
CValue2::CValue2(void)
	: MValue(0)
{
	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - DEFAULT CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValue2::CValue2(int Value)
	: MValue(Value)
{
	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValue2::CValue2(const CValue2& Other)
	: MValue(Other.MValue)
{
	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - COPY CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValue2::CValue2(CValue2&& Other) noexcept
	: MValue(Other.MValue)
{
	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - MOVE CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CValue2::~CValue2(void) noexcept
{
	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValue2& CValue2::operator=(const CValue2& Other)
{
	MValue=Other.MValue;

	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - COPY OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CValue2& CValue2::operator=(CValue2&& Other) noexcept
{
	MValue=Other.MValue;

	wcout << L"VALUE 2 - VALUE [" << MValue << L"] - MOVE OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CValue2::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------