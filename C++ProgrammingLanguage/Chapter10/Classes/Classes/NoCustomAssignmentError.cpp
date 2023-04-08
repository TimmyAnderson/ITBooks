//-------------------------------------------------------------------------------------------------------
#include "NoCustomAssignmentError.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignmentError::CNoCustomAssignmentError(void)
	: MStringValue(L""), MIntValue(0), MConst(100)
{
	wprintf_s(L"DEFAULT CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignmentError::CNoCustomAssignmentError(wstring StringValue, int IntValue)
	: MStringValue(StringValue), MIntValue(IntValue), MConst(100)
{
	wprintf_s(L"CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CNoCustomAssignmentError::~CNoCustomAssignmentError(void)
{
	wprintf_s(L"DESTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CNoCustomAssignmentError::PrintValue(void)
{
	wprintf_s(L"String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------