//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationClassParameters.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFullTemplateSpecializationClassParameters<void>::CFullTemplateSpecializationClassParameters(TYPE Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFullTemplateSpecializationClassParameters<void>::~CFullTemplateSpecializationClassParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString CFullTemplateSpecializationClassParameters<void>::Print(void) const
{
	wstringstream												Stream;

	Stream << L"TEMPLATE CLASS SPECIALIZATION <void> - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"] VALUE [" << MValue << L"]." << endl;

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFullTemplateSpecializationClassParameters<CString,CString>::CFullTemplateSpecializationClassParameters(const CString& Value1, const CString& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFullTemplateSpecializationClassParameters<CString,CString>::~CFullTemplateSpecializationClassParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString CFullTemplateSpecializationClassParameters<CString,CString>::Print(void) const
{
	wstringstream												Stream;

	Stream << L"TEMPLATE CLASS SPECIALIZATION <CString,CString> - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"] VALUE 1 [" << MValue1 << L"] VALUE 2 [" << MValue2 << L"]." << endl;

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------