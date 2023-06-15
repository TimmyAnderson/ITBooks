//----------------------------------------------------------------------------------------------------------------------
#include "CPerfectForwardingInConstructorTemplateEnableIf.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateEnableIf::CPerfectForwardingInConstructorTemplateEnableIf(const CPerfectForwardingInConstructorTemplateEnableIf& Value)
	: MValue(Value.MValue)
{
	wcout << L"TEMPLATE - COPY CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateEnableIf::CPerfectForwardingInConstructorTemplateEnableIf(CPerfectForwardingInConstructorTemplateEnableIf&& Value) noexcept
	: MValue(move(Value.MValue))
{
	wcout << L"TEMPLATE - MOVE CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateEnableIf::~CPerfectForwardingInConstructorTemplateEnableIf(void) noexcept
{
	wcout << L"TEMPLATE - DESTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CPerfectForwardingInConstructorTemplateEnableIf::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------