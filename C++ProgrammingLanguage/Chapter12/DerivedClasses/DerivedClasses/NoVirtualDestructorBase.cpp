//-------------------------------------------------------------------------------------------------------
#include "NoVirtualDestructorBase.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CNoVirtualDestructorBase::CNoVirtualDestructorBase(void)
{
	wprintf_s(L"CNoVirtualDestructorBase CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CNoVirtualDestructorBase::~CNoVirtualDestructorBase(void)
{
	wprintf_s(L"CNoVirtualDestructorBase DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------