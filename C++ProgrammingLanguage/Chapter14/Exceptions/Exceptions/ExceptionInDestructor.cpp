//-------------------------------------------------------------------------------------------------------
#include "ExceptionInDestructor.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CExceptionInDestructor::CExceptionInDestructor(void)
{
}
//-------------------------------------------------------------------------------------------------------
CExceptionInDestructor::~CExceptionInDestructor(void)
{
	throw(L"EXCEPTION in DESTRUCTOR !");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CExceptionInDestructor::DoNothing(void)
{
	wprintf_s(L"DoNothing() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------