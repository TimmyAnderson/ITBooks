//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationClassSyntax.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! KEYWORD [template<>] sa NESMIE pouzit pre TEMPLATE MEMBERS TEMPLATE CLASS SPECIALIZATIONS, ktore maju DEFINITION OUT OF CLASS.
//template<>
CString CFullTemplateSpecializationClassSyntax<void>::ToString(void) const
{
	CString														Text(L"SIMPLE - TEMPLATE CLASS SPECIALIZATION <void>.");

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------