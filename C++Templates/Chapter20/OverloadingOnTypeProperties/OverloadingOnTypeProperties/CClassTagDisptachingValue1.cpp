//----------------------------------------------------------------------------------------------------------------------
#include "CClassTagDisptachingValue1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CClassTagDisptachingValue1::CClassTagDisptachingValue1(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CClassTagDisptachingValue1::~CClassTagDisptachingValue1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CClassTagDisptachingValue1::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wostream& operator<<(wostream& Stream, const CClassTagDisptachingValue1& Value)
{
	Stream << Value.MValue;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------