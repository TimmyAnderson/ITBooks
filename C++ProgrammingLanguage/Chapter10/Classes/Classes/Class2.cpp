//-------------------------------------------------------------------------------------------------------
#include "Class2.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CClass2::CClass2(void)
{
	wprintf_s(L"Class2 CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CClass2::CClass2(int Dummy)
{
	wprintf_s(L"Class2 NON-DEFAULT CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CClass2::~CClass2(void)
{
	wprintf_s(L"Class2 DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------