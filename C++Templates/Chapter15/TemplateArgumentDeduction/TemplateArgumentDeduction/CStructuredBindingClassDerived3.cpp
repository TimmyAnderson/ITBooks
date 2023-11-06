//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingClassDerived3.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingClassDerived3::CStructuredBindingClassDerived3(const CString& PublicFieldDerived1, int PublicFieldDerived2, const CString& PublicFieldBase11, int PublicFieldBase12, double PublicFieldBase21, const CString& PublicFieldBase22)
	: CStructuredBindingClassBase1(PublicFieldBase11,PublicFieldBase12), CStructuredBindingClassBase2(PublicFieldBase21,PublicFieldBase22), MPublicFieldDerived1(PublicFieldDerived1), MPublicFieldDerived2(PublicFieldDerived2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingClassDerived3::~CStructuredBindingClassDerived3(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CString& CStructuredBindingClassDerived3::GetPublicFieldDerived1(void) const noexcept
{
	return(MPublicFieldDerived1);
}
//----------------------------------------------------------------------------------------------------------------------
int CStructuredBindingClassDerived3::GetPublicFieldDerived2(void) const noexcept
{
	return(MPublicFieldDerived2);
}
//----------------------------------------------------------------------------------------------------------------------