//-------------------------------------------------------------------------------------------------------
#include "VirtualDestructorBase.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CVirtualDestructorBase::CVirtualDestructorBase(void)
{
	wprintf_s(L"CVirtualDestructorBase CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CVirtualDestructorBase::~CVirtualDestructorBase(void)
{
	wprintf_s(L"CVirtualDestructorBase DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------