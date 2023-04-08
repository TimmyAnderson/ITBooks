//-------------------------------------------------------------------------------------------------------
#include "ComplexClass.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// !!! V CONSTRUCTORS FIELDS moze dojst k hodeniu EXCEPTION.
CComplexClass::CComplexClass(bool ThrowExceptionInClassA, bool ThrowExceptionInClassB, bool ThrowExceptionInComplexClass)
	: MClassA(ThrowExceptionInClassA), MClassB(ThrowExceptionInClassB)
{
	wprintf_s(L"CComplexClass CONSTRUCTOR CALLED !\n");

	if (ThrowExceptionInComplexClass==true)
	{
		wprintf_s(L"CComplexClass is THROWING EXCEPTION !\n");
		throw(L"CComplexClass EXCEPTION !");
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! V CONSTRUCTORS FIELDS moze dojst k hodeniu EXCEPTION.
// !!!!!! SPECIALNA SYNTAX na zachytanie EXCEPTIONS, ktore vzniknu v INITIALIZERS.
CComplexClass::CComplexClass(bool ThrowExceptionInClassA, bool ThrowExceptionInClassB, bool ThrowExceptionInComplexClass, bool Dummy)
try
	: MClassA(ThrowExceptionInClassA), MClassB(ThrowExceptionInClassB)
{
	// TELO CONSTRUCTOR.

	wprintf_s(L"CComplexClass CONSTRUCTOR CALLED !\n");

	if (ThrowExceptionInComplexClass==true)
	{
		wprintf_s(L"CComplexClass is THROWING EXCEPTION !\n");
		throw(L"CComplexClass EXCEPTION !");
	}
}
catch(wchar_t* Exception)
{
	// !!! CATCH BLOCK pre CONSTRUCTOR.

	wprintf_s(L"EXCEPTION in CONSTRUCTOR [%s] !\n",Exception);

	// !!!!! Tu C++ AUTOMATICKY GENERUJE znova EXCEPTION. Spravi teda EXCEPTION RE-THROWN.
}
//-------------------------------------------------------------------------------------------------------
CComplexClass::~CComplexClass(void)
{
	wprintf_s(L"CComplexClass DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CComplexClass::DoNothing(void)
{
	wprintf_s(L"void CComplexClass::DoNothing(void) CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------