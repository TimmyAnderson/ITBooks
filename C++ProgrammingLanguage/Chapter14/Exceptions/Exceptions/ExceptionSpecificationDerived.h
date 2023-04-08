//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <new>
#include "ExceptionSpecificationBase.h"
#include "ExceptionBase.h"
#include "ExceptionDerived.h"
//-------------------------------------------------------------------------------------------------------
class CExceptionSpecificationDerived : public CExceptionSpecificationBase
{
	public:
		virtual void ThrowCExceptionBase(void) throw (CExceptionBase);
		virtual void ThrowCExceptionDerived(void) throw (CExceptionDerived);

		// !!!!! Visual C++ toto SKOMPILUJE, aj keby NEMAL, kedze sa jedna o MENEJ RESTRIKTIVNU EXCEPTION SPECIFICATION.
		//virtual void ThrowCExceptionBase(void) throw (CExceptionDerived);

		// !!! Toto je OK, lebo DERIVED METHOD definuje mwenej restriktivny EXCEPTION SPECIFICATION.
		//virtual void ThrowCExceptionDerived(void) throw (CExceptionBase);

		// !!!!! Aj toto C++ CHYBNE SKOMPILUJE aj ked NESEDIA EXCEPTION SPECIFICATIONS.
		//virtual void ThrowCExceptionDerived(void) throw (std::bad_alloc);

	public:
		CExceptionSpecificationDerived(void);
		virtual ~CExceptionSpecificationDerived(void);
};
//-------------------------------------------------------------------------------------------------------