//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "ExceptionBase.h"
#include "ExceptionDerived.h"
//-------------------------------------------------------------------------------------------------------
class CExceptionSpecificationBase
{
	public:
		virtual void ThrowCExceptionBase(void) throw (CExceptionBase);
		virtual void ThrowCExceptionDerived(void) throw (CExceptionDerived);

	public:
		CExceptionSpecificationBase(void);
		virtual ~CExceptionSpecificationBase(void);
};
//-------------------------------------------------------------------------------------------------------