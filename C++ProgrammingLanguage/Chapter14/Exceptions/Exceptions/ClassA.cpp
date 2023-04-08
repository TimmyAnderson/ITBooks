//-------------------------------------------------------------------------------------------------------
#include "ClassA.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CClassA::CClassA(bool ThrowException)
{
	wprintf_s(L"CClassA CONSTRUCTOR CALLED !\n");

	if (ThrowException==true)
	{
		wprintf_s(L"CClassA is THROWING EXCEPTION !\n");
		throw(L"CClassA EXCEPTION !");
	}
}
//-------------------------------------------------------------------------------------------------------
CClassA::~CClassA(void)
{
	wprintf_s(L"CClassA DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------