//----------------------------------------------------------------------------------------------------------------------
#include "CThrowException.h"
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CThrowException::CThrowException(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
CThrowException::CThrowException(const CThrowException&)
{
	throw(CException(L"EXCEPTION in COPY CONSTRUCTOR."));
}
//----------------------------------------------------------------------------------------------------------------------
CThrowException::~CThrowException(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CThrowException& CThrowException::operator=(const CThrowException&)
{
	throw(CException(L"EXCEPTION in OPERATOR [OPERATOR=]."));
}
//----------------------------------------------------------------------------------------------------------------------