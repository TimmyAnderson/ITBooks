//----------------------------------------------------------------------------------------------------------------------
#include "CPerfectForwardingInConstructorTemplate.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplate::CPerfectForwardingInConstructorTemplate(const CPerfectForwardingInConstructorTemplate& Value)
	: MValue(Value.MValue)
{
	wcout << L"TEMPLATE - COPY CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplate::CPerfectForwardingInConstructorTemplate(CPerfectForwardingInConstructorTemplate&& Value) noexcept
	: MValue(move(Value.MValue))
{
	wcout << L"TEMPLATE - MOVE CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplate::~CPerfectForwardingInConstructorTemplate(void) noexcept
{
	wcout << L"TEMPLATE - DESTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CPerfectForwardingInConstructorTemplate::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------