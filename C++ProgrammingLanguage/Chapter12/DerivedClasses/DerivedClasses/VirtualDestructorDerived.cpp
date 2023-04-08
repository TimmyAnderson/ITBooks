//-------------------------------------------------------------------------------------------------------
#include "VirtualDestructorDerived.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CVirtualDestructorDerived::CVirtualDestructorDerived(void)
{
	wprintf_s(L"CVirtualDestructorDerived CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CVirtualDestructorDerived::~CVirtualDestructorDerived(void)
{
	wprintf_s(L"CVirtualDestructorDerived DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------