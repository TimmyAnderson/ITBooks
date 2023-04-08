//-------------------------------------------------------------------------------------------------------
#include "NewDeleteOperators.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CNewDeleteOperators::CNewDeleteOperators(void)
{
	wprintf_s(L"CONSTRUCTOR CALLED and EXCEPTION will be THROWN !\n");

	throw(L"Some EXCEPTION !");
}
//-------------------------------------------------------------------------------------------------------
CNewDeleteOperators::~CNewDeleteOperators(void)
{
	wprintf_s(L"DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void* CNewDeleteOperators::operator new(size_t Size)
{
	wprintf_s(L"void* CNewDeleteOperators::operator new(size_t Size) CALLED !\n");

	__int8*														Buffer=::new __int8[Size];

	return(Buffer);
}
//-------------------------------------------------------------------------------------------------------
void CNewDeleteOperators::operator delete(void* Object)
{
	wprintf_s(L"void CNewDeleteOperators::operator delete(void* Object) CALLED !\n");

	::delete[](Object);
}
//-------------------------------------------------------------------------------------------------------