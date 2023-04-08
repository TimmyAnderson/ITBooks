//-------------------------------------------------------------------------------------------------------
#include "CErrorThisChildShared.h"
#include "CErrorThisParentShared.h"
//-------------------------------------------------------------------------------------------------------
CErrorThisChildShared::CErrorThisChildShared(std::shared_ptr<CErrorThisParentShared> Parent)
	: MParent(Parent)
{
	wprintf_s(L"METHOD CErrorThisChildShared::CErrorThisChildShared() CALLED ! REFERENCE COUNTER [%d] !\n",MParent.use_count());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CErrorThisChildShared::CallParent(void)
{
	MParent->SomeMethod();
}
//-------------------------------------------------------------------------------------------------------