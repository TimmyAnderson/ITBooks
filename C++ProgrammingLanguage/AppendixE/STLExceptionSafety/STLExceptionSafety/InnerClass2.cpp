//-------------------------------------------------------------------------------------------------------
#include "InnerClass2.h"
#include <stdio.h>
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CInnerClass2::CInnerClass2(int Value)
{
	wprintf_s(L"CInnerClass2 CONSTRUCTOR CALLED !\n");

	if (Value==2)
	{
		throw(wstring(L"CInnerClass2 THROWN EXCEPTION !"));
	}
}
//-------------------------------------------------------------------------------------------------------
CInnerClass2::~CInnerClass2(void)
{
	wprintf_s(L"CInnerClass2 DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------