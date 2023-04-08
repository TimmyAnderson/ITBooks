//-------------------------------------------------------------------------------------------------------
#include "CErrorThisChildShared.h"
#include "CErrorThisParentShared.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CErrorThisChildShared::CErrorThisChildShared(std::shared_ptr<CErrorThisParentShared> Parent)
	: MParent(Parent)
{
	wcout << L"METHOD CErrorThisChildShared::CErrorThisChildShared() CALLED ! REFERENCE COUNTER [" << MParent.use_count() << L"] !" << endl;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CErrorThisChildShared::CallParent(void)
{
	MParent->SomeMethod();
}
//-------------------------------------------------------------------------------------------------------