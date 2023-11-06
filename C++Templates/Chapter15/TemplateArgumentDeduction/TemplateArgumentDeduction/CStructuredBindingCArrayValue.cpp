//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingCArrayValue.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue::CStructuredBindingCArrayValue(void)
	: MValue(0)
{
	wcout << L"VALUE - VALUE [" << MValue << L"] - DEFAULT CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue::CStructuredBindingCArrayValue(int Value)
	: MValue(Value)
{
	wcout << L"VALUE - VALUE [" << MValue << L"] - CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue::CStructuredBindingCArrayValue(const CStructuredBindingCArrayValue& Other)
	: MValue(Other.MValue)
{
	wcout << L"VALUE - VALUE [" << MValue << L"] - COPY CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue::CStructuredBindingCArrayValue(CStructuredBindingCArrayValue&& Other) noexcept
	: MValue(Other.MValue)
{
	wcout << L"VALUE - VALUE [" << MValue << L"] - MOVE CONSTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue::~CStructuredBindingCArrayValue(void) noexcept
{
	wcout << L"VALUE - VALUE [" << MValue << L"] - DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue& CStructuredBindingCArrayValue::operator=(const CStructuredBindingCArrayValue& Other)
{
	MValue=Other.MValue;

	wcout << L"VALUE - VALUE [" << MValue << L"] - COPY OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingCArrayValue& CStructuredBindingCArrayValue::operator=(CStructuredBindingCArrayValue&& Other) noexcept
{
	MValue=Other.MValue;

	wcout << L"VALUE - VALUE [" << MValue << L"] - MOVE OPERATOR= CALLED !" << endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CStructuredBindingCArrayValue::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
void CStructuredBindingCArrayValue::SetValue(int Value) noexcept
{
	MValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wostream& operator<<(wostream& Stream, const CStructuredBindingCArrayValue& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------