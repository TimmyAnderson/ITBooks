//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPAndRestrictedTemplateExpansionDerived.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCRTPAndRestrictedTemplateExpansionDerived::CCRTPAndRestrictedTemplateExpansionDerived(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCRTPAndRestrictedTemplateExpansionDerived::~CCRTPAndRestrictedTemplateExpansionDerived(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CCRTPAndRestrictedTemplateExpansionDerived::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------