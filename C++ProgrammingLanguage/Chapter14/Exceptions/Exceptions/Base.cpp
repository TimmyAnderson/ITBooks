//-------------------------------------------------------------------------------------------------------
#include "Base.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CBase::CBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
CBase::CBase(const CBase& Original)
{
	wprintf_s(L"CBase COPY CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CBase::~CBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBase::PrintError(void)
{
	wprintf_s(L"void CBase::PrintError(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------