//----------------------------------------------------------------------------------------------------------------------
#include "CPerfectForwardingInConstructorNoTemplate.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorNoTemplate::CPerfectForwardingInConstructorNoTemplate(const wstring& Value)
	: MValue(Value)
{
	wcout << L"NO TEMPLATE - STRING COPY CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorNoTemplate::CPerfectForwardingInConstructorNoTemplate(wstring&& Value)
	: MValue(move(Value))
{
	wcout << L"NO TEMPLATE - STRING MOVE CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorNoTemplate::CPerfectForwardingInConstructorNoTemplate(const CPerfectForwardingInConstructorNoTemplate& Value)
	: MValue(Value.MValue)
{
	wcout << L"NO TEMPLATE - COPY CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorNoTemplate::CPerfectForwardingInConstructorNoTemplate(CPerfectForwardingInConstructorNoTemplate&& Value) noexcept
	: MValue(move(Value.MValue))
{
	wcout << L"NO TEMPLATE - MOVE CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorNoTemplate::~CPerfectForwardingInConstructorNoTemplate(void) noexcept
{
	wcout << L"NO TEMPLATE - DESTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CPerfectForwardingInConstructorNoTemplate::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------