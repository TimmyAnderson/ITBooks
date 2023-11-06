//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingClassDerived2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingClassDerived2::CStructuredBindingClassDerived2(const CString& PublicFieldDerived1, int PublicFieldDerived2, const CString& PublicFieldBase1, int PublicFieldBase2)
	: CStructuredBindingClassBase1(PublicFieldBase1,PublicFieldBase2), MPublicFieldDerived1(PublicFieldDerived1), MPublicFieldDerived2(PublicFieldDerived2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CStructuredBindingClassDerived2::~CStructuredBindingClassDerived2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CString& CStructuredBindingClassDerived2::GetPublicFieldDerived1(void) const noexcept
{
	return(MPublicFieldDerived1);
}
//----------------------------------------------------------------------------------------------------------------------
int CStructuredBindingClassDerived2::GetPublicFieldDerived2(void) const noexcept
{
	return(MPublicFieldDerived2);
}
//----------------------------------------------------------------------------------------------------------------------