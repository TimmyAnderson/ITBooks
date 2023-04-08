//-------------------------------------------------------------------------------------------------------
// !!!!! Visual C++ 10 GENERUJE WARINING pri pouziti EXCEPTION SPECIFICATIONS, kedze ich NEPODPORUJE.
#pragma warning(disable : 4290)
//-------------------------------------------------------------------------------------------------------
#include "ExceptionSpecificationBase.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CExceptionSpecificationBase::CExceptionSpecificationBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
CExceptionSpecificationBase::~CExceptionSpecificationBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CExceptionSpecificationBase::ThrowCExceptionBase(void) throw (CExceptionBase)
{
	wprintf_s(L"CExceptionSpecificationBase::ThrowCExceptionBase(void) CALLED !\n");

	throw(CExceptionBase());
}
//-------------------------------------------------------------------------------------------------------
void CExceptionSpecificationBase::ThrowCExceptionDerived(void) throw (CExceptionDerived)
{
	wprintf_s(L"CExceptionSpecificationBase::ThrowCExceptionDerived(void) CALLED !\n");

	throw(CExceptionDerived());
}
//-------------------------------------------------------------------------------------------------------