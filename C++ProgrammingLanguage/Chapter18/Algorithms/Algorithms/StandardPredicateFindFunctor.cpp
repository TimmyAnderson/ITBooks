//-------------------------------------------------------------------------------------------------------
#include "StandardPredicateFindFunctor.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CStandardPredicateFindFunctor::CStandardPredicateFindFunctor(wstring ValueToCompare)
	: MValueToCompare(ValueToCompare)
{
}
//-------------------------------------------------------------------------------------------------------
CStandardPredicateFindFunctor::~CStandardPredicateFindFunctor(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
bool CStandardPredicateFindFunctor::operator()(wstring Param)
{
	if (Param==MValueToCompare)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------