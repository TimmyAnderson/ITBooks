//-------------------------------------------------------------------------------------------------------
#include "NoCustomAssignment.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignment::CNoCustomAssignment(void)
	: MStringValue(L""), MIntValue(0)
{
	wprintf_s(L"DEFAULT CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignment::CNoCustomAssignment(wstring StringValue, int IntValue)
	: MStringValue(StringValue), MIntValue(IntValue)
{
	wprintf_s(L"CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignment::~CNoCustomAssignment(void)
{
	wprintf_s(L"DESTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CNoCustomAssignment::PrintValue(void)
{
	wprintf_s(L"String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------