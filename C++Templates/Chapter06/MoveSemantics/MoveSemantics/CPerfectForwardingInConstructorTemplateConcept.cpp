//----------------------------------------------------------------------------------------------------------------------
#include "CPerfectForwardingInConstructorTemplateConcept.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateConcept::CPerfectForwardingInConstructorTemplateConcept(const CPerfectForwardingInConstructorTemplateConcept& Value)
	: MValue(Value.MValue)
{
	wcout << L"TEMPLATE - COPY CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateConcept::CPerfectForwardingInConstructorTemplateConcept(CPerfectForwardingInConstructorTemplateConcept&& Value) noexcept
	: MValue(move(Value.MValue))
{
	wcout << L"TEMPLATE - MOVE CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CPerfectForwardingInConstructorTemplateConcept::~CPerfectForwardingInConstructorTemplateConcept(void) noexcept
{
	wcout << L"TEMPLATE - DESTRUCTOR CALLED with VALUE [" << MValue << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CPerfectForwardingInConstructorTemplateConcept::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------