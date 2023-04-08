//-------------------------------------------------------------------------------------------------------
// !!!!! Visual C++ 10 GENERUJE WARINING pri pouziti EXCEPTION SPECIFICATIONS, kedze ich NEPODPORUJE.
#pragma warning(disable : 4290)
//-------------------------------------------------------------------------------------------------------
#include "ExceptionSpecificationDerived.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CExceptionSpecificationDerived::CExceptionSpecificationDerived(void)
{
}
//-------------------------------------------------------------------------------------------------------
CExceptionSpecificationDerived::~CExceptionSpecificationDerived(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CExceptionSpecificationDerived::ThrowCExceptionBase(void) throw (CExceptionBase)
{
	wprintf_s(L"CExceptionSpecificationDerived::ThrowCExceptionBase(void) CALLED !\n");

	throw(CExceptionBase());
}
//-------------------------------------------------------------------------------------------------------
void CExceptionSpecificationDerived::ThrowCExceptionDerived(void) throw (CExceptionDerived)
{
	wprintf_s(L"CExceptionSpecificationDerived::ThrowCExceptionDerived(void) CALLED !\n");

	throw(CExceptionDerived());
}
//-------------------------------------------------------------------------------------------------------