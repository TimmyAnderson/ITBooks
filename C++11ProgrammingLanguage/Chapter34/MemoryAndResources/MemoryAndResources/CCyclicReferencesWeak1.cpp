//-------------------------------------------------------------------------------------------------------
#include "CCyclicReferencesWeak1.h"
#include "CCyclicReferencesWeak2.h"
//-------------------------------------------------------------------------------------------------------
void CCyclicReferencesWeak1::CallOther(void)
{
	MPointer.lock()->SomeMethod();
}
//-------------------------------------------------------------------------------------------------------