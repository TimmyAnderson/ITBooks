//-------------------------------------------------------------------------------------------------------
#include "CCyclicReferencesShared1.h"
#include "CCyclicReferencesShared2.h"
//-------------------------------------------------------------------------------------------------------
void CCyclicReferencesShared1::CallOther(void)
{
	MPointer->SomeMethod();
}
//-------------------------------------------------------------------------------------------------------