//-------------------------------------------------------------------------------------------------------
#include "CovarianceDerived.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CDummyDerived													CCovarianceDerived::MDummyDerived;
CCovarianceDerived												CCovarianceDerived::MCovarianceDerived;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CCovarianceDerived::CCovarianceDerived(void)
{
}
//-------------------------------------------------------------------------------------------------------
CCovarianceDerived::~CCovarianceDerived(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CCovarianceDerived::PrintText(void)
{
	wprintf_s(L"CCovarianceDerived - PrintText() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CDummyDerived* CCovarianceDerived::GetDummy(void)
{
	return(&MDummyDerived);
}
//-------------------------------------------------------------------------------------------------------
CCovarianceDerived* CCovarianceDerived::GetCovariance(void)
{
	return(&MCovarianceDerived);
}
//-------------------------------------------------------------------------------------------------------