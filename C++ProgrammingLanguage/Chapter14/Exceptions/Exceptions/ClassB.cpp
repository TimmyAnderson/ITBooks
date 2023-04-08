//-------------------------------------------------------------------------------------------------------
#include "ClassB.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CClassB::CClassB(bool ThrowException)
{
	wprintf_s(L"CClassB CONSTRUCTOR CALLED !\n");

	if (ThrowException==true)
	{
		wprintf_s(L"CClassB is THROWING EXCEPTION !\n");
		throw(L"CClassB EXCEPTION !");
	}
}
//-------------------------------------------------------------------------------------------------------
CClassB::~CClassB(void)
{
	wprintf_s(L"CClassB DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------