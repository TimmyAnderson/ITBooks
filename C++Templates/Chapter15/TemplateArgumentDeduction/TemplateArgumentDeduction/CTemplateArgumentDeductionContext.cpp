//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateArgumentDeductionContext.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTemplateArgumentDeductionContext::CTemplateArgumentDeductionContext(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CTemplateArgumentDeductionContext::~CTemplateArgumentDeductionContext(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
double CTemplateArgumentDeductionContext::Multiple2(const int& Value) const
{
	double														Result=(Value*2.0);

	wcout << L"METHOD - FIELD [" << MField << L"] PARAMETER [" << Value << L"] RETURN VALUE [" << Result << L"]." << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------