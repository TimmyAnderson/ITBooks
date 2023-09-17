//----------------------------------------------------------------------------------------------------------------------
#include "CLookUpQualifiedNamesDerived.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CLookUpQualifiedNamesDerived::CLookUpQualifiedNamesDerived(const CString& Field1, const CString& Field2)
	: CLookUpQualifiedNamesBase(Field1), MField(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
CLookUpQualifiedNamesDerived::~CLookUpQualifiedNamesDerived(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const CString& CLookUpQualifiedNamesDerived::GetBaseField(void) const
{
	// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR::].
	const CString&												Field=CLookUpQualifiedNamesBase::MField;

	return(Field);
}
//----------------------------------------------------------------------------------------------------------------------
const CString& CLookUpQualifiedNamesDerived::GetDerivedField(void) const
{
	// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR::].
	const CString&												Field=CLookUpQualifiedNamesDerived::MField;

	return(Field);
}
//----------------------------------------------------------------------------------------------------------------------