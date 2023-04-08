#include "stdafx.h"
#include "BasicMathClass.h"
//-------------------------------------------------------------------------------------------------------
STDMETHODIMP CBasicMathClass::Add(LONG A, LONG B, LONG* Result)
{
	*Result=A+B;

	return(S_OK);
}
//-------------------------------------------------------------------------------------------------------