//-------------------------------------------------------------------------------------------------------
#include "ClassDereferencing.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CClassDereferencing::CClassDereferencing(CPointerToClassDereferencing Object)
	: MObject(Object)
{
}
//-------------------------------------------------------------------------------------------------------
CClassDereferencing::~CClassDereferencing(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CPointerToClassDereferencing CClassDereferencing::operator->(void)
{
	wprintf(L"CClassDereferencing::OPERATOR->() CALLED !\n");

	return(MObject);
}
//-------------------------------------------------------------------------------------------------------