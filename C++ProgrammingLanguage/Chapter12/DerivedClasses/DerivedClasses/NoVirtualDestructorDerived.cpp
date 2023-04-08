//-------------------------------------------------------------------------------------------------------
#include "NoVirtualDestructorDerived.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CNoVirtualDestructorDerived::CNoVirtualDestructorDerived(void)
{
	wprintf_s(L"CNoVirtualDestructorDerived CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CNoVirtualDestructorDerived::~CNoVirtualDestructorDerived(void)
{
	wprintf_s(L"CNoVirtualDestructorDerived DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------