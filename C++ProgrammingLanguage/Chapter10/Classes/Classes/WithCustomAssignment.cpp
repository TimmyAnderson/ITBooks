//-------------------------------------------------------------------------------------------------------
#include "WithCustomAssignment.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CWithCustomAssignment::CWithCustomAssignment(void)
	: MStringValue(L""), MIntValue(0)
{
	wprintf_s(L"DEFAULT CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CWithCustomAssignment::CWithCustomAssignment(wstring StringValue, int IntValue)
	: MStringValue(StringValue), MIntValue(IntValue)
{
	wprintf_s(L"CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CWithCustomAssignment::CWithCustomAssignment(const CWithCustomAssignment& OrginalObject)
	: MStringValue(OrginalObject.MStringValue), MIntValue(OrginalObject.MIntValue)
{
	wprintf_s(L"COPY CONSTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
CWithCustomAssignment::~CWithCustomAssignment(void)
{
	wprintf_s(L"DESTRUCTOR - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CWithCustomAssignment& CWithCustomAssignment::operator=(const CWithCustomAssignment& OriginalObject)
{
	MStringValue=OriginalObject.MStringValue;
	MIntValue=OriginalObject.MIntValue;

	wprintf_s(L"OPERATOR ASSIGNMENET - String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CWithCustomAssignment::PrintValue(void)
{
	wprintf_s(L"String: [%s], Int: [%d] !\n",MStringValue.c_str(),MIntValue);
}
//-------------------------------------------------------------------------------------------------------