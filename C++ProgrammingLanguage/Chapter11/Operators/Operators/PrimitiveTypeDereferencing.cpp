//-------------------------------------------------------------------------------------------------------
#include "PrimitiveTypeDereferencing.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CPrimitiveTypeDereferencing::CPrimitiveTypeDereferencing(int* Pointer)
	: MPointer(Pointer)
{
}
//-------------------------------------------------------------------------------------------------------
CPrimitiveTypeDereferencing::~CPrimitiveTypeDereferencing(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int* CPrimitiveTypeDereferencing::operator->(void)
{
	wprintf(L"CSimpleDereferencing::OPERATOR->() CALLED !\n");

	return(MPointer);
}
//-------------------------------------------------------------------------------------------------------