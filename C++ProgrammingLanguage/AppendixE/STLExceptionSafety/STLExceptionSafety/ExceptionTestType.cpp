//-------------------------------------------------------------------------------------------------------
#include "ExceptionTestType.h"
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CExceptionTestType::CExceptionTestType(int Value)
	: MValue(Value)
{
}
//-------------------------------------------------------------------------------------------------------
CExceptionTestType::CExceptionTestType(const CExceptionTestType& Value)
	: MValue(Value.MValue)
{
	if (MValue==55)
	{
		throw(wstring(L"MY EXCEPTION - Can't CALL COPY CONSTRUCTOR for value 55 !"));
	}

	static bool													FirstTime=true;

	if (MValue==100)
	{
		if (FirstTime==true)
		{
			FirstTime=false;
		}
		else
		{
			throw(wstring(L"MY EXCEPTION - Can't CALL COPY CONSTRUCTOR for value 100 !"));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
CExceptionTestType::~CExceptionTestType(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CExceptionTestType& CExceptionTestType::operator=(const CExceptionTestType& Other)
{
	if (Other.MValue==100)
	{
		throw(wstring(L"MY EXCEPTION - Can't ASSIGN value 100 !"));
	}

	MValue=Other.MValue;

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
bool CExceptionTestType::operator<(const CExceptionTestType& Other)
{
	if (MValue==3)
	{
		throw(wstring(L"MY EXCEPTION - Can't COMPARE value 3 !"));
	}

	if (MValue<Other.MValue)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int CExceptionTestType::GetValue(void) const
{
	return(MValue);
}
//-------------------------------------------------------------------------------------------------------