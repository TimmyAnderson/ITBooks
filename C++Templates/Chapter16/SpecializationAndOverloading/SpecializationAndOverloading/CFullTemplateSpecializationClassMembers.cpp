//----------------------------------------------------------------------------------------------------------------------
#include "CFullTemplateSpecializationClassMembers.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! KEYWORD [template<>] sa NESMIE pouzit pre TEMPLATE MEMBERS TEMPLATE CLASS SPECIALIZATIONS, ktore maju DEFINITION OUT OF CLASS.
//template<>
void CFullTemplateSpecializationClassMembersOutside<CString>::PrintTemplateSpecializationOutside(const CString& Value) const
{
	wcout << L"OUTSIDE - TEMPLATE SPECIALIZATION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------