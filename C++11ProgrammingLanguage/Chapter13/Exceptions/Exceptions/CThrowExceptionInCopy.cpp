//-----------------------------------------------------------------------------
#include "CThrowExceptionInCopy.h"
#include "CException.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CThrowExceptionInCopy::CThrowExceptionInCopy(const wstring& Value)
	: MValue(Value)
{
	wcout << L"CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
CThrowExceptionInCopy::CThrowExceptionInCopy(const CThrowExceptionInCopy& Value)
	: MValue(Value.MValue)
{
	wcout << L"!!!!! COPY CONSTRUCTOR [" << __func__ << L"()] CALLED !" << endl;

	// !!! Hodi EXCEPTION pri COPY CONSTRUCTOR.
	throw(CException(L"THROW EXCEPTION in COPY CONSTRUCTOR !!!"));
}
//-----------------------------------------------------------------------------
CThrowExceptionInCopy::~CThrowExceptionInCopy(void)
{
	wcout << L"DESTRUCTOR [" << __func__ << L"()] CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CThrowExceptionInCopy& CThrowExceptionInCopy::operator=(const CThrowExceptionInCopy& Value)
{
	wcout << L"!!!!! COPY OPERATOR= [CThrowExceptionInCopy] CALLED !" << endl;

	// !!! Hodi EXCEPTION pri COPY OPERATOR=.
	throw(CException(L"THROW EXCEPTION in COPY OPERATOR= !!!"));

	MValue=Value.MValue;

	return(*this);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wstring& CThrowExceptionInCopy::GetValue(void) const noexcept
{
	return(MValue);
}
//-----------------------------------------------------------------------------