//-------------------------------------------------------------------------------------------------------
#include "EEnum.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
EEnum& operator++(EEnum& Enum, int DummyOperand)
{
	wprintf(L"GLOBAL OPERATOR++(EEnum&,int) !\n");

	Enum=(EEnum) (Enum+1);

	return(Enum);
}
//-------------------------------------------------------------------------------------------------------